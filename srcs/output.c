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
	if (nb_args >= -1 && nb_args <= 1)
		return (lowRegs(nb_args, regs));
	else if (nb_args >= 2 && nb_args <= 4)
		return (mediumRegs(nb_args, regs));
	else
		return (highRegs(nb_args, regs));
	return (0);
}


void			printArg(char *type, int nb_args, struct user_regs_struct *regs)
{
	int	i = 0;
	
	if (type[strlen(type) - 1] == '*' && strcmp(type, "char *") && strcmp(type, "char **"))
	{
		if (nb_args != -1)
			fprintf(stderr, "\"");
		printPointer(getGoodRegister(nb_args, regs));
		if (nb_args != -1)
			fprintf(stderr, "\"");
	}
	else
	{
		while (g_types[i + 1].name != NULL && strcmp(g_types[i].name, type))
			++i;
		if (nb_args != -1)
			fprintf(stderr, "\"");
		g_types[i].printFct(getGoodRegister(nb_args, regs));
		if (nb_args != -1)
			fprintf(stderr, "\"");
	}
}

void			printRet(int nb_syscall, char *type, struct user_regs_struct *regs)
{
	fprintf(stderr, ") = ");
	if (nb_syscall != 60 && nb_syscall != 231)
	{
		if ((long long)regs->rax < 0)
			fprintf(stderr, "-1 (%s)", strerror(-regs->rax));
		else
			printArg(type, -1, regs);
	}
	else
		fprintf(stderr, "?");
	(void)fprintf(stderr, "\n");
}

void			printAllArgs(int nb_syscall, struct user_regs_struct *regs)
{
	int	i = 0;

	for (int i = 0; i < g_syscalls[nb_syscall].nb_params - 1; i++)
	{
		printArg(g_syscalls[nb_syscall].params[i], i, regs);
		fprintf(stderr, ", ");
	}
	printArg(g_syscalls[nb_syscall].params[i], i, regs);
}

int			printCall(int nb_syscall, struct user_regs_struct *regs)
{
	(void *)regs;

	fprintf(stderr, "%s(", g_syscalls[nb_syscall].name);
	printAllArgs(nb_syscall, regs);
	return (1);
}