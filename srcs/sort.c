/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

extern sFLag;

void	sortInt(unsigned long long int regs)
{
	checkParamAdd(&regs);
	if (sFlag == 0)
		fprintf(stderr, "%d", (int)regs);
	else
		fprintf(stderr, "%p", (int*)&regs);
	isGood();	
}

void	sortLong(unsigned long long int regs)
{
	checkParamAdd(&regs);
	if (sFlag == 0)
		fprintf(stderr, "%ld", (long)regs);
	else
		fprintf(stderr, "%p", (long *)regs);
}

void	sortUint(unsigned long long int regs)
{
	checkParamAdd(&regs);
	if (sFlag == 0)
		fprintf(stderr, "%u", (unsigned int)regs);
	else
		fprintf(stderr, "%p", (unsigned int *)regs);
}

void	sortUlong(unsigned long long int regs)
{
	checkParamAdd(&regs);
	if (sFlag == 0)
		fprintf(stderr, "%lu", (unsigned long)regs);
	else
		fprintf(stderr, "%p", (unsigned long *)regs);
}

void	sortPointer(unsigned long long int regs)
{
	checkParamAdd(&regs);
	if (regs == 0)
		fprintf(stderr, "NULL");
	else
		fprintf(stderr, "%p", (void*)regs);
	isGood();
}
