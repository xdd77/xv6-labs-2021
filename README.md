# xv6-labs-2021 学习记录

这是我的 MIT 6.S081 Operating System Engineering 学习仓库。

本项目基于 MIT xv6 教学操作系统，通过完成各个 lab 逐步理解现代操作系统核心机制，包括进程管理、系统调用、虚拟内存、陷阱机制、文件系统以及并发控制等。

学习过程中不仅完成实验代码，也记录源码分析、设计思想以及调试过程。

课程主页：
https://pdos.csail.mit.edu/6.S081/2021/

---

## Learning Progress

按照 MIT 6.S081 实验顺序学习：

- [x] Lab util - Unix utilities
- [x] Lab syscall - System calls
- [x] Lab pgtbl - Page tables
- [ ] Lab traps - Trap mechanisms
- [ ] Lab lazy - Lazy allocation
- [ ] Lab cow - Copy-on-write fork
- [ ] Lab thread - Multithreading
- [ ] Lab lock - Kernel locks
- [ ] Lab fs - File system
- [ ] Lab mmap - Memory mapping

---

# 已完成内容

## Lab util

学习内容：

- Unix 进程模型
- fork / exec / pipe
- 用户程序与 xv6 系统调用接口

---

## Lab syscall

学习内容：

- 系统调用流程
- 用户态到内核态切换
- trapframe 保存用户上下文
- syscall 分发机制

---

## Lab pgtbl - Page Tables

完成内容：

### 1. 虚拟内存与页表

理解：

- Virtual Address 到 Physical Address 转换
- RISC-V Sv39 三级页表
- VPN[2] / VPN[1] / VPN[0]
- Page Table Entry(PTE)
- 多级页表为什么节省内存

---

### 2. vmprint

实现页表递归打印：

- 理解页表树结构
- 理解有效 PTE(PTE_V)
- 分析用户地址空间布局
- 理解 TRAMPOLINE、TRAPFRAME、USYSCALL 映射

---

### 3. Speed up system calls

实现 USYSCALL 页面：

- 为进程创建用户可读页面
- 将 pid 映射到用户空间
- 减少简单系统调用开销

涉及：

- proc.c
- proc.h
- memlayout.h
- 页表映射

---

### 4. pgaccess

实现访问页面检测：

- PTE_A Access Bit
- walk() 查找页表项
- 修改 PTE 状态
- copyout 返回结果

---

# 学习笔记方向

## xv6 内存管理核心关系

```
Process
   |
   +-- pagetable
          |
          +-- VA -> PTE -> PA
```

用户程序使用虚拟地址，CPU 通过页表完成地址转换。

---

## 页表转换流程

```
Virtual Address
        |
        v
VPN[2]
        |
        v
VPN[1]
        |
        v
VPN[0]
        |
        v
PTE
        |
        v
Physical Address
```

---

# 后续学习计划

继续深入：

1. Trap 机制与用户/内核态切换
2. 系统调用完整执行流程
3. 进程调度与上下文切换
4. 锁与并发控制
5. 文件系统设计
6. 内存映射机制

目标：通过 xv6 源码理解操作系统核心设计思想。
