/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

void	printInt(unsigned long long int regs)
{
	(void)fprintf(stderr, "%d", (int)regs);
}

void	printLong(unsigned long long int regs)
{
	(void)fprintf(stderr, "%ld", (long)regs);
}

void	printUint(unsigned long long int regs)
{
	(void)fprintf(stderr, "%u", (unsigned int)regs);
}

void	printUlong(unsigned long long int regs)
{
	(void)fprintf(stderr, "%lu", (unsigned long)regs);
}

void	printPointer(unsigned long long int regs)
{
	if (regs == 0)
		fprintf(stderr, "NULL");
	else
		(void)fprintf(stderr, "%p", (void*)regs);
}
