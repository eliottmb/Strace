/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

extern pid_t	g_tracee_pid;

static void	printChar(char c)
{
	if (((c > 32 && c < 127) || c == ' ') && c != '\0')
		(void)fprintf(stderr, "%c", c);
	else if (c != '\n' && c != '\0')
		(void)fprintf(stderr, "\\%o", c);
}

void	printString(unsigned long long int regsVal)
{
	int	i;
	long	c;
	
	(void)fprintf(stderr, "\"");
	i = 0;
	c = -1;

	for (int i = 0; ((char)c != '\0' && i < 42); i = i + 1)
	{
		if ((c = ptrace(PTRACE_PEEKDATA, g_tracee_pid, regsVal, NULL)) == -1)
		{
			fprintf(stderr, "\033[36mptrace PTRACE_PEEK_DATA error: ");
			fprintf(stderr, "%s\033[33m\"", strerror(errno));
			return ;
		}
		printChar(c);
		++regsVal;
	}
	(void)fprintf(stderr, "\"");
}

void			printStringTab(unsigned long long int regsVal)
{
	unsigned long long	str;
	int			i;
	
	(void)fprintf(stderr, "[");
	i = 0;
	str = (unsigned long long)-1;
	while ((void*)str != NULL && i < 6)
	{
		if ((str = ptrace(PTRACE_PEEKDATA, g_tracee_pid, regsVal, NULL)) == (unsigned long long)-1)
		{
			fprintf(stderr, "\033[36mptrace PTRACE_PEEK_DATA error: ");
			fprintf(stderr, "%s\033[33m]", strerror(errno));
			return ;
		}
		if (str)
		printString(str);
		regsVal += sizeof(char*);
		++i;
	}
	(void)fprintf(stderr, "]");
		if (i >= 6)
	(void)fprintf(stderr, " ... ");
}

void	printUnimplemented(unsigned long long int regsVal)
{
	(void)regsVal;
	(void)fprintf(stderr, "unimplemented");
}

void	printNothing(unsigned long long int regsVal)
{
	(void)regsVal;
}
