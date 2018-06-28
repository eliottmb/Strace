/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#ifndef		__STRACE_H__
# define	__STRACE_H__

#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/user.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>
#include <poll.h>
#include <sys/times.h>

int forked(int ac, char **av);
int my_trace(pid_t pid);
int syswait(pid_t pid);
void	printSyscall(int call);
void	printParam(int param);
void	printRet(int ret);

//void	printit(pid_t pid, int call, int ret)

#endif      /* __STRACE_H__ */
