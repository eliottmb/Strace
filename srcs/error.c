/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

void	checkStatus(int status)
{
	int	*p = &status;
	//printf("%d\n", status);
	return ;
}

int	checkCall()
{
	return (0);
}

void	checkRegs(struct user_regs_struct *regs)
{
	struct user_regs_struct *registers = regs;
	//printf("%p\n", registers);
}

void	checkParamAdd(void *ptr)
{
	void	*next = ptr + 1;

	//printf("%p\n", ptr);
	//printf("%p\n", next);
}

void	isGood()
{
	//printf("All good that far\n");
}