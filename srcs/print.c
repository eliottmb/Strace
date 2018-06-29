/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

extern pid_t	g_pid;

static void	printChar(char c)
{
	if (((c > 32 && c < 127) || c == ' ') && c != '\0')
		fprintf(stderr, "%c", c);
	else if (c != '\n' && c != '\0')
		fprintf(stderr, "\\%o", c);
}

void	printString(unsigned long long int regsVal)
{
	int	i;
	long	c;
	
	fprintf(stderr, "\"");
	i = 0;
	c = -1;

	for (int i = 0; ((char)c != '\0' && i < 42); i = i + 1)
	{
		if ((c = ptrace(PTRACE_PEEKDATA, g_pid, regsVal, NULL)) == -1)
		{
			fprintf(stderr, "ptrace PTRACE_PEEK_DATA error");
			return ;
		}
		printChar(c);
		++regsVal;
	}
	fprintf(stderr, "\"");
}

void			printStringTab(unsigned long long int regsVal)
{
	unsigned long long	str;
	int			i;
	
	fprintf(stderr, "[");
	i = 0;
	while ((void*)str != NULL && i < 6)
	{
		if ((str = ptrace(PTRACE_PEEKDATA, g_pid, regsVal, NULL)) == (unsigned long long)-1)
		{
			fprintf(stderr, "ptrace PTRACE_PEEK_DATA error");
			return ;
		}
		if (str)
		printString(str);
		regsVal += sizeof(char*);
		++i;
	}
	fprintf(stderr, "]");
		if (i >= 6)
	fprintf(stderr, " ... ");
}

void	printNope(unsigned long long int regsVal)
{
	fprintf(stderr, "unimplemented");
}

void	printNothing(unsigned long long int regsVal)
{
	return;
}
