# xv6-labs-2021 学习记录

这是我的 MIT 6.S081（Operating System Engineering）学习仓库。

我按照课程官方安排逐步学习 xv6，通过完成实验理解操作系统的进程、系统调用、虚拟内存、陷阱、并发和文件系统，并在学习笔记中记录实现思路、问题与调试过程。

- [MIT 6.S081 2021 课程主页](https://pdos.csail.mit.edu/6.S081/2021/)
- [课程安排](https://pdos.csail.mit.edu/6.S081/2021/schedule.html)

## 学习进度

- [x] **Lab 1：Unix utilities** 

- [x] **Lab 2：System calls** —  [lab2笔记1](https://github.com/user-attachments/files/30769431/xv6_lab2_trace_notes_cn.docx)
[lab2笔记2](https://github.com/user-attachments/files/30769430/xv6_Lab2_sysinfo_.docx)
- [x] **Lab 3：Page tables（学习中）** — [Lab3笔记](https://github.com/user-attachments/files/30776201/xv6_Lab3_Page_tables_.docx)
- [x] Lab 4：Traps  [Lab 4.docx](https://github.com/user-attachments/files/31552432/Traps.docx)
- [ ] Lab 5：Lazy allocation
- [ ] Lab 6：Copy-on-write fork
- [ ] Lab 7：Multithreading
- [ ] Lab 8：Locks
- [ ] Lab 9：File system
- [ ] Lab 10：mmap

## 当前学习重点

### Lab 1：Unix utilities

`fork`、`exec`、`wait`、`pipe`、进程流水线、目录递归与用户程序设计。

### Lab 2：System calls

用户态到内核态的系统调用路径、系统调用分发、参数获取、`copyout`、进程表与空闲内存统计。

### Lab 3：Page tables

RISC-V Sv39 三级页表、VA → PTE → PA、`walk`、`mappages`、`vmprint`、TRAMPOLINE、TRAPFRAME、USYSCALL、PTE_A 与 `pgaccess`。
###Lab 4:Trap

类似于中断，在遇到一些syscall等都会陷入新的需要执行的trap中，这个地方需要重点的去掌握 secp等寄存器的作用，以及proc.h中我们为进程初始化添加了新的属性，其中我觉得理解trapframe是必要的，trapframe负责新建一块新的地址空间，我们可以在这一块新的内存中去为sys的trap中处理中间的一些寄存器的备份，以便于返回主程序时可以正常运行。

## 说明

各实验代码保存在对应分支，默认分支的 README 与 `docs/` 用于汇总整个课程的学习进度和笔记。
