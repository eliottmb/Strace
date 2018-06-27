/*
** EPITECH PROJECT, 2018
** strargce
** File description:
** Syscall tracer
*/

#include "output.h"

void	printit(pid_t pid, int call, int ret)
{
	if (call > 0 && call <= 313)
		printf("call (%s) = %d\n", g_syscalls[call].name);
}
