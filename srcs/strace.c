/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

pid_t	g_pid = -1;

extern t_prototype	g_syscalls[];

void		quitErr(char *str)
{
	fprintf(stderr, "s\n");
	exit(84);
}

int		next(pid_t pid, int *status)
{
	checkStatus(status);
  	if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
	      	quitErr("trace PTRACE_SINGLESTEP error");
	if (waitpid(pid, status, 0) == -1)
    		quitErr("wait error");
      	return (1);
}

int		getCall(struct user_regs_struct *regs, pid_t pid, int *status)
{
	unsigned long long	callNumber;

	callNumber = regs->rax;
	checkStatus(status);
  	if (callNumber > 313 || printCall(callNumber, regs) == 0)
		return (checkCall());
	if (callNumber != 60 && callNumber != 231)
	{
		if (callNumber == 1)
			fprintf(stderr, "\n");
		if (next(pid, status) == 0 || ptrace(PTRACE_GETREGS, pid, NULL, regs) == -1)
		return (0);
	}
	printRet(callNumber, g_syscalls[callNumber].ret_type, regs);
	if (callNumber == 60 || callNumber == 231)
		exit(EXIT_SUCCESS);
	return (1);
}

int		getRegs(struct user_regs_struct *regs, pid_t pid, int *status)
{
	long			rip_pointed_data;
	
	checkStatus(status);
	checkParamAdd(regs);
  	if ((rip_pointed_data = ptrace(PTRACE_PEEKDATA, pid, regs->rip, NULL)) == -1)
		return (0);
	rip_pointed_data &= 0xffff;
	if (rip_pointed_data == 0x50f)
	{
		checkRegs(regs);
		if (getCall(regs, pid, status) == 0)
			return (0);
	}
	return (1);
}

int		trace(pid_t pid)
{
	struct user_regs_struct		regs;
	int				status;

	if (waitpid(pid, &status, 0) == -1)
		quitErr("wait error");
	while (42)
	{
	if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) == -1)
		quitErr("ptrace PTRACE_GETREGS error");
	checkRegs(&regs);
	if (getRegs(&regs, pid, &status) == 0)
		return (0);
	checkParamAdd(&status);
	if (next(pid, &status) == 0)
		return (0);
	}
}
