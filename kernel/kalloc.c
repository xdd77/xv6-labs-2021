// Physical memory allocator, for user processes,
// kernel stacks, page-table pages,
// and pipe buffers. Allocates whole 4096-byte pages.

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

void freerange(void *pa_start, void *pa_end);

extern char end[]; // first address after kernel.
                   // defined by kernel.ld.

struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist;
} kmem;

#define NPAGES ((PHYSTOP - KERNBASE) / PGSIZE)
struct {
  struct spinlock lock;
  int cnt[NPAGES];
}refcnt;
static int 
pa2idx(uint64 pa)
{
  if(pa < KERNBASE || pa >= PHYSTOP)
    panic("pa2idx");
  return (pa - KERNBASE) / PGSIZE;
}


void
kinit()
{
  initlock(&kmem.lock, "kmem");
  
  initlock(&refcnt.lock,"refcnt");

  freerange(end, (void*)PHYSTOP);
}

void
freerange(void *pa_start, void *pa_end)
{
  char *p;
  p = (char*)PGROUNDUP((uint64)pa_start);
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE){
    acquire(&refcnt.lock);
    refcnt.cnt[pa2idx((uint64)p)] = 1;
    release(&refcnt.lock);
    kfree(p);
  }
}

// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(void *pa)
{
  struct run *r;
  int idx;
  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");


  idx = pa2idx((uint64)pa);
  acquire(&refcnt.lock);
  if(refcnt.cnt[idx] < 1)
    panic("kfree ref");
  refcnt.cnt[idx] --;
  
  if(refcnt.cnt[idx] > 0)
  {
    release(&refcnt.lock);
    return ;
  }
  release(&refcnt.lock);


  // Fill with junk to catch dangling refs.
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;

  acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
  release(&kmem.lock);
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *
kalloc(void)
{
  struct run *r;

  acquire(&kmem.lock);
  r = kmem.freelist;
  //从freelist中拿取一页空闲的地址
  if(r)
    kmem.freelist = r->next;
  release(&kmem.lock);

  if(r){
    memset((char*)r, 5, PGSIZE); // fill with junk

    //kalloc后说明肯定有一个地方正在使用这张物理页
    acquire(&refcnt.lock);
    refcnt.cnt[pa2idx((uint64)r)] = 1;
    release(&refcnt.lock);
  }
  return (void*)r;
}

//在我们COW fork后child指向parent的pa,但是这里没有用kalloc(后边用到写操作再kalloc);
//所以需要手动给给parent的pa加上一个计数引用，使用krefinc
void krefinc(uint64 pa)
{
  int idx = pa2idx(pa);
  acquire(&refcnt.lock);
  if(refcnt.cnt[idx] < 1){
    panic("krefinc");
  }
  refcnt.cnt[idx] ++;
  release(&refcnt.lock);
}


int
krefcnt(uint64 pa)
{
  int n;

  acquire(&refcnt.lock);
  n = refcnt.cnt[pa2idx(pa)];
  release(&refcnt.lock);

  return n;
}