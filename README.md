# xv6-labs-2021 学习记录

这是我的 MIT 6.S081（Operating System Engineering）学习仓库。

我按照课程官方安排逐步学习 xv6，通过完成实验理解操作系统的进程、系统调用、虚拟内存、陷阱、并发和文件系统，并在学习笔记中记录实现思路、问题与调试过程。

- [MIT 6.S081 2021 课程主页](https://pdos.csail.mit.edu/6.S081/2021/)
- [课程安排](https://pdos.csail.mit.edu/6.S081/2021/schedule.html)

## 学习进度

- [x] **Lab 1：Unix utilities** 

- [x] **Lab 2：System calls** —  [lab2笔记1](https://github.com/user-attachments/files/30769431/xv6_lab2_trace_notes_cn.docx)
[lab2笔记2](https://github.com/user-attachments/files/30769430/xv6_Lab2_sysinfo_.docx)
- [x] **Lab 3：Page tables（学习中）** — [xv6_Lab3_Page_tables_完整回顾与实现推导指南.docx](https://github.com/user-attachments/files/30776201/xv6_Lab3_Page_tables_.docx)
- [ ] Lab 4：Traps
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

## 说明

各实验代码保存在对应分支，默认分支的 README 与 `docs/` 用于汇总整个课程的学习进度和笔记。
