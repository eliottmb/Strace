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

int forked(int ac, char **av);
int my_trace(pid_t pid);
int syswait(pid_t pid);

char *getstr(pid_t pid, unsigned long addr);
//void	printit(pid_t pid, int call, int ret)

#endif      /* __STRACE_H__ */
