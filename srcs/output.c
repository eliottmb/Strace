/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

extern t_calls		g_calls[];
extern t_fctTab		g_params[];


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


void			sortArg(char *type, int nb_args, struct user_regs_struct *regs)
{
	int	i = 0;
	
	if (type[strlen(type) - 1] == '*' && strcmp(type, "char *") && strcmp(type, "char **"))
	{
		if (nb_args != -1)
			fprintf(stderr, "\"");
		sortPointer(getGoodRegister(nb_args, regs));
		if (nb_args != -1)
			fprintf(stderr, "\"");
	}
	else
	{
		while (g_params[i + 1].name != NULL && strcmp(g_params[i].name, type))
			++i;
		if (nb_args != -1)
			fprintf(stderr, "\"");
		g_params[i].sortFct(getGoodRegister(nb_args, regs));
		if (nb_args != -1)
			fprintf(stderr, "\"");
	}
}

void			sortRet(int nb_syscall, char *type, struct user_regs_struct *regs)
{
	fprintf(stderr, ") = ");
	if (nb_syscall != 60 && nb_syscall != 231)
	{
		if ((long long)regs->rax < 0)
			fprintf(stderr, "-1 (%s)", strerror(-regs->rax));
		else
			sortArg(type, -1, regs);
	}
	else
		fprintf(stderr, "?");
	(void)fprintf(stderr, "\n");
}

void			sortAllArgs(int nb_syscall, struct user_regs_struct *regs)
{
	int	i = 0;

	for (int i = 0; i < g_calls[nb_syscall].nb_params - 1; i++)
	{
		sortArg(g_calls[nb_syscall].params[i], i, regs);
		fprintf(stderr, ", ");
	}
	sortArg(g_calls[nb_syscall].params[i], i, regs);
}

int			sortCall(int nb_syscall, struct user_regs_struct *regs)
{
	(void *)regs;

	fprintf(stderr, "%s(", g_calls[nb_syscall].name);
	sortAllArgs(nb_syscall, regs);
	return (1);
}