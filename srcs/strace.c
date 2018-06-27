/*
** EPITECH PROJECT, 2018
** strargce
** File description:
** Syscall tracer
*/

#include "strace.h"

#define VALUE (4096)

int	syswait(pid_t pid)
{
	int 	stat;
	int 	syscall;
	int	ret;
	
	int	params, params2;
	while(1)
	{
		//ptrace(PTRACE_SYSCALL, pid, 0, 0);
		ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
		waitpid(pid, &stat, 0);
		//printf("sig = %d\n", WSTOPSIG(stat));
		if (WIFSTOPPED(stat) && WSTOPSIG(stat) == SIGTRAP)
		{
			
			//printf("Just catch signal\n");
			syscall = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * ORIG_RAX);
			//params = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * RBX);
			//params2 = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * RCX);
      			ret = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * RAX);
			if (syscall > 0 && syscall < 313)
				printit(pid, syscall, ret);
		}
		if (WIFEXITED(stat))
			return (1);
	}
	return (0);
}

int	forked(int argc, char **argv)
{
	char *ag[argc + 1];

	memcpy(ag, argv, argc * sizeof(char * ));
	ag[argc] = NULL;
	ptrace(PTRACE_TRACEME);
	kill(getpid(), SIGSTOP);
	return (execvp(ag[0], ag));
}

int	my_trace(pid_t pid)
{
	int status, syscall, ret;
	int bg = 1;

	waitpid(pid, &status, 0);
	ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);
	while (bg)
	{
		if (syswait(pid) != 0)
			break;
		syscall = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * ORIG_RAX);
      /*      	if (syswait(pid) != 0)
	      	break;*/
		ret = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * RAX);
		printit(pid, syscall, ret, 0, 0);
	}
	puts("----");
	return (0);
}

char	*getstr(pid_t pid, unsigned long addr)
{
	char		*s = malloc(VALUE);
	unsigned int	alloc = VALUE;
	int		read =0;
	unsigned long	tmp;

	while(1)
	{
		if ((read + sizeof (tmp)) > alloc)
		{
			alloc *= 2;
			s = realloc(s, alloc);
		}
		tmp = ptrace(PTRACE_PEEKDATA, pid, addr + read);
		if (errno != 0)
		{
			s[read] = 0;
			break;
		}
		memcpy(s + read, &tmp, sizeof(tmp));
		if (memchr(&tmp, 0, sizeof(tmp)) != NULL)
			break;
		read += sizeof(tmp);
	}
	return (s);
}
