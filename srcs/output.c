/*
** EPITECH PROJECT, 2018
** strargce
** File description:
** Syscall tracer
*/

#include "output.h"

void	printit(pid_t pid, int call, int ret)
{
	//char *s1 = getstr(pid, params);
	//char *s2 = getstr(pid, params2);
	if (call > 0 && call <= 55)
		printf("call (%s) = %d\n", g_syscalls[call].name);
	else
		printf("call (%d) = %d\n", call, ret);
}
