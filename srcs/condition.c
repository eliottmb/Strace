/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

unsigned long long	lowRegs(int nb_args, struct user_regs_struct *regs)
{
	if (nb_args == -1)
		return (regs->rax);
	else if (nb_args == 0)
		return (regs->rdi);
	else
		return (regs->rsi);
}
unsigned long long	mediumRegs(int nb_args, struct user_regs_struct *regs)
{
	if (nb_args == 2)
		return (regs->rdx);
	if (nb_args == 3)
		return (regs->rcx);
	if (nb_args == 4)
		return (regs->r8);
	return (0);
	
}
unsigned long long	highRegs(int nb_args, struct user_regs_struct *regs)
{
	if (nb_args == 5)
		return (regs->r9);
	return (0);
}

void			sortNothing(unsigned long long int regsVal)
{
	return;
}