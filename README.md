# xv6-labs-2021 学习记录

这是我的 MIT 6.S081 Operating System Engineering 学习仓库。

通过完成 MIT xv6 labs，逐步理解操作系统核心机制，并记录源码分析、实验思考和调试过程。

课程主页：
https://pdos.csail.mit.edu/6.S081/2021/

## Learning Progress

- [x] Lab1 util - Unix utilities
  - 学习笔记：`docs/Lab1_Unix_utilities_学习笔记.docx`
- [x] Lab2 syscall - System calls
  - 学习笔记：`docs/Lab2_Sysinfo_实现与源码理解指南.docx`
- [x] Lab3 pgtbl - Page tables
  - 学习笔记：`docs/Lab3_Page_tables_实现与源码理解指南.docx`
- [ ] Lab4 traps - Trap mechanisms
- [ ] Lab5 lazy - Lazy allocation
- [ ] Lab6 cow - Copy-on-write fork
- [ ] Lab7 thread - Multithreading
- [ ] Lab8 lock - Kernel locks
- [ ] Lab9 fs - File system
- [ ] Lab10 mmap - Memory mapping

## 学习重点

### Lab1 util

- fork / exec / wait
- pipe 进程通信
- 用户程序与系统调用接口

### Lab2 syscall

- 用户态到内核态切换
- syscall 分发流程
- trapframe
- 用户地址与内核地址交互

### Lab3 pgtbl

- RISC-V Sv39 三级页表
- VA -> PTE -> PA
- walk / mappages
- vmprint
- TRAMPOLINE、TRAPFRAME、USYSCALL
- PTE_A 与 pgaccess

## 后续目标

继续按照 MIT 6.S081 官方实验顺序学习 xv6：

1. Trap 机制
2. 进程切换
3. 虚拟内存优化
4. 并发与锁
5. 文件系统

目标：通过 xv6 源码理解现代操作系统设计思想。