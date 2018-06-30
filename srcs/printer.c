/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

extern sFLag;

void	printInt(unsigned long long int regs)
{
	if (sFlag == 0)
		fprintf(stderr, "%d", (int)regs);
	else
		fprintf(stderr, "%p", (int*)&regs);
}

void	printLong(unsigned long long int regs)
{
	if (sFlag == 0)
		fprintf(stderr, "%ld", (long)regs);
	else
		fprintf(stderr, "%p", (long *)regs);
}

void	printUint(unsigned long long int regs)
{
	if (sFlag == 0)
		fprintf(stderr, "%u", (unsigned int)regs);
	else
		fprintf(stderr, "%p", (unsigned int *)regs);
}

void	printUlong(unsigned long long int regs)
{
	if (sFlag == 0)
		fprintf(stderr, "%lu", (unsigned long)regs);
	else
		fprintf(stderr, "%p", (unsigned long *)regs);
}

void	printPointer(unsigned long long int regs)
{
	if (regs == 0)
		fprintf(stderr, "NULL");
	else
		fprintf(stderr, "%p", (void*)regs);
}
