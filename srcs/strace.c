/*
** EPITECH PROJECT, 2018
** strargce
** File description:
** Syscall tracer
*/

#include "strace.h"
#include <sys/ptrace.h>

#define VALUE (4096)

int	syswait(pid_t pid)
{
	int 	stat;
	int 	syscall;
	int	ret;
	struct user_regs_struct regs;
				
	int	params, params2;
	while(1)
	{
		ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
		waitpid(pid, &stat, 0);
		if (WIFSTOPPED(stat) && WSTOPSIG(stat) == SIGTRAP)
		{
			syscall = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * ORIG_RAX), NULL;
			ret = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * RAX, NULL);
			params = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * RBX, NULL);
			if (syscall > 0 && syscall < 15)
			{
				printSyscall(syscall);
				printParam(params);
				printRet(ret);
			}
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
	int	status;
	int	syscall;
	int	ret;
	int	params;
	
	waitpid(pid, &status, 0);
	ptrace(PTRACE_SETOPTIONS, pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (syswait(pid) != 0)
			break;
		syscall = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * ORIG_RAX);
		params = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * RBX, NULL);
		ret = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * RAX);
		printSyscall(syscall);
		printParam(params);
		printRet(ret);
	}
	puts("----");
	return (0);
}