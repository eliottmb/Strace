/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

extern pid_t	g_pid;

static void		sortChar(char c)
{
	if (((c > 32 && c < 127) || c == ' ') && c != '\0')
	{
		if (sFlag == 0)
			fprintf(stderr, "%c", c);
		else 
			fprintf(stderr, "%p", (char *)c);
	}
	else if (c != '\n' && c != '\0')
		fprintf(stderr, "\\%o", c);
}

void			sortStringPtr(unsigned long long int regsVal)
{
	long	c = -1;

	checkParamAdd(&regsVal);
	c = ptrace(PTRACE_PEEKDATA, g_pid, regsVal, NULL);
	sortPointer(c);
}

void			sortString(unsigned long long int regsVal)
{
	int	i;
	long	c;
	
	i = 0;
	c = -1;
	checkParamAdd(&regsVal);
	if (sFlag == 1)
		sortStringPtr(regsVal);
	else
	{
		for (int i = 0; ((char)c != '\0' && i < 42); i = i + 1)
		{
			if ((c = ptrace(PTRACE_PEEKDATA, g_pid, regsVal, NULL)) == -1)
				quitErr("ptrace PTRACE_PEEK_DATA error\n");
			sortChar(c);
			++regsVal;
		}
	}
}

void			sortStringTab(unsigned long long int regsVal)
{
	unsigned long long	str;
	int			i;
	
	fprintf(stderr, "[");
	i = 0;
	checkParamAdd(&regsVal);
	while ((void*)str != NULL && i < 6)
	{
		if ((str = ptrace(PTRACE_PEEKDATA, g_pid, regsVal, NULL)) == (unsigned long long)-1)
		{
			fprintf(stderr, "ptrace PTRACE_PEEK_DATA error");
			return ;
		}
		if (str)
		sortString(str);
		regsVal += sizeof(char*);
		++i;
	}
	fprintf(stderr, "]");
		if (i >= 6)
	fprintf(stderr, " ... ");
}

void			sortNope(unsigned long long int regsVal)
{
	fprintf(stderr, "unimplemented");
}