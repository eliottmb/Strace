/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

extern t_prototype	g_syscalls[];
extern t_types		g_types[];

unsigned long long int	getGoodRegister(int nb_args, struct user_regs_struct *regs)
{
	if (nb_args == -1)
		return (regs->rax);
	if (nb_args == 0)
		return (regs->rdi);
	if (nb_args == 1)
		return (regs->rsi);
	if (nb_args == 2)
		return (regs->rdx);
	if (nb_args == 3)
		return (regs->rcx);
	if (nb_args == 4)
		return (regs->r8);
	if (nb_args == 5)
		return (regs->r9);
	return (0);
}

void	printArg(char *type, int nb_args, struct user_regs_struct *regs)
{
	int	i;
	
	i = 0;
	if (type[strlen(type) - 1] == '*' && strcmp(type, "char *") && strcmp(type, "char **"))
		printPointer(getGoodRegister(nb_args, regs));
	else
	{
		while (g_types[i + 1].name != NULL && strcmp(g_types[i].name, type))
			++i;
		g_types[i].print_fct(getGoodRegister(nb_args, regs));
	}
}

void	printRet(int nb_syscall, char *type, struct user_regs_struct *regs)
{
	(void)fprintf(stderr, ") = ");
	if (nb_syscall != 60 && nb_syscall != 231)
	{
		if ((long long)regs->rax < 0)
			fprintf(stderr, "-1 (%s)", strerror(-regs->rax));
		else
			printArg(type, -1, regs);
	}
	else
		fprintf(stderr, "?");
	(void)fprintf(stderr, "\033[0m\n");
}

void	printAllArgs(int nb_syscall, struct user_regs_struct *regs)
{
	int	i = 0;

	for (int i = 0; i < g_syscalls[nb_syscall].nb_params - 1; i++)
	{
		printArg(g_syscalls[nb_syscall].params[i], i, regs);
		fprintf(stderr, ", ");
	}
	printArg(g_syscalls[nb_syscall].params[i], i, regs);
}

int	printCall(int nb_syscall, struct user_regs_struct *regs)
{
	(void *)regs;

	fprintf(stderr, "%s", g_syscalls[nb_syscall].name);
	fprintf(stderr, "(");
	printAllArgs(nb_syscall, regs);
	return (SUCCESS);
}