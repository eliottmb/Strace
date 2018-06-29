/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

pid_t	g_tracee_pid = -1;

extern t_prototype	g_syscalls[];

static int	step_instruction(pid_t pid, int *status)
{
  if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
    {
      warn("trace PTRACE_SINGLESTEP error");
      return (FAILURE);
    }
  if (waitpid(pid, status, 0) == -1)
    {
      warn("wait error");
      return (FAILURE);
    }
  return (SUCCESS);
}

static int		analyse_syscall(struct user_regs_struct *registers, pid_t pid, int *status)
{
  unsigned long long	callNumber;

  callNumber = registers->rax;
  if (callNumber > MAX_SYSCALL || printCall(callNumber, registers) == FAILURE)
    return (FAILURE);
  if (callNumber != 60 && callNumber != 231)
    {
      if (callNumber == 1)
	fprintf(stderr, "\n");
      if (step_instruction(pid, status) == FAILURE
	  || ptrace(PTRACE_GETREGS, pid, NULL, registers) == -1)
	return (FAILURE);
    }
  printRet(callNumber, g_syscalls[callNumber].ret_type, registers);
  if (callNumber == 60 || callNumber == 231)
    {
	printf(" was returned by tracee");
	system("echo -n $?");
	printf("\n");
      exit(EXIT_SUCCESS);
    }
  return (SUCCESS);
}

static int		analyse_registers(struct user_regs_struct *registers,
					  pid_t pid, int *status)
{
  long			rip_pointed_data;

  if ((rip_pointed_data = ptrace(PTRACE_PEEKDATA, pid, registers->rip, NULL)) == -1)
    return (FAILURE);
  rip_pointed_data &= 0xffff;
  if (rip_pointed_data == SYSCALL_OPCODE)
    {
      if (analyse_syscall(registers, pid, status) == FAILURE)
	return (FAILURE);
    }
  return (SUCCESS);
}

int				trace(pid_t pid)
{
  struct user_regs_struct	registers;
  int				status;

  if (waitpid(pid, &status, 0) == -1)
    {
      warn("wait error");
      return (FAILURE);
    }
  while (42)
    {
      if (ptrace(PTRACE_GETREGS, pid, NULL, &registers) == -1)
	{
	  warn("ptrace PTRACE_GETREGS error");
	  return (FAILURE);
	}
      if (analyse_registers(&registers, pid, &status) == FAILURE)
	return (FAILURE);
      if (step_instruction(pid, &status) == FAILURE)
	return (FAILURE);
    }
}
