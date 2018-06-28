/*
** EPITECH PROJECT, 2018
** strargce
** File description:
** Syscall tracer
*/

#include "output.h"

#define VALUE (4096)

void	printSyscall(int call)
{
	printf("call %s", g_syscalls[call].name);
}

void	printParam(int param)
{
	printf("(%d) ", param);
}

void	printRet(int ret)
{
	printf("%d\n", ret);
}