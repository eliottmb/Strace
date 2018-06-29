/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

pid_t	g_pid = -1;

extern t_prototype	g_syscalls[];

static int	step_instruction(pid_t pid, int *status)
{
  	if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
	      	quitErr("trace PTRACE_SINGLESTEP error");
	if (waitpid(pid, status, 0) == -1)
    		quitErr("wait error");
      	return (1);
}

static int		analyse_syscall(struct user_regs_struct *regs, pid_t pid, int *status)
{
	unsigned long long	callNumber;

	callNumber = regs->rax;
	if (callNumber > 313 || printCall(callNumber, regs) == 0)
		return (0);
	if (callNumber != 60 && callNumber != 231)
	{
		if (callNumber == 1)
			fprintf(stderr, "\n");
		if (step_instruction(pid, status) == 0 || ptrace(PTRACE_GETREGS, pid, NULL, regs) == -1)
		return (0);
	}
	printRet(callNumber, g_syscalls[callNumber].ret_type, regs);
	if (callNumber == 60 || callNumber == 231)
	{
		//printf(" was returned by tracee");
		//system("echo -n $?");
		// printf("\n");
		exit(EXIT_SUCCESS);
	}
	return (1);
}

static int		analyse_regs(struct user_regs_struct *regs, pid_t pid, int *status)
{
	long			rip_pointed_data;
	
	if ((rip_pointed_data = ptrace(PTRACE_PEEKDATA, pid, regs->rip, NULL)) == -1)
		return (0);
	rip_pointed_data &= 0xffff;
	if (rip_pointed_data == 0x50f)
	{
		if (analyse_syscall(regs, pid, status) == 0)
			return (0);
	}
	return (1);
}

int				trace(pid_t pid)
{
	struct user_regs_struct		regs;
	int				status;

	if (waitpid(pid, &status, 0) == -1)
		quitErr("wait error");
	while (42)
	{
	if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) == -1)
		quitErr("ptrace PTRACE_GETREGS error");
	if (analyse_regs(&regs, pid, &status) == 0)
		return (0);
	if (step_instruction(pid, &status) == 0)
		return (0);
	}
}
