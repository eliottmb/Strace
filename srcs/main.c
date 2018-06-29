/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

extern pid_t	g_tracee_pid;

int	launch_child(char **cmd)
{
	if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
	{
		warn("ptrace PTRACE_TRACEME error");
		return (FAILURE);
	}
	execvp(*cmd, cmd);
	warn("execvp error");
	return (FAILURE);
}

static int	trace_by_pid(pid_t pid)
{
	if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1)
	{
		warn("ptrace PTRACE_ATTACH error");
		return (FAILURE);
	}
	g_tracee_pid = pid;
	if (trace_process(pid) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	trace_by_cmd(char **cmd)
{
	pid_t	child;

	if ((child = fork()) == -1)
	{
		warn("fork error");
		return (FAILURE);
	}
	if (child == 0)
	{
		if (launch_child(cmd) == FAILURE)
			exit(EXIT_FAILURE);
	}
	else
	{
		g_tracee_pid = child;
		if (trace_process(child) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static void	sig_handler(int signum)
{
	(void)signum;

	if (ptrace(PTRACE_DETACH, g_tracee_pid, NULL, NULL) == -1)
		warn("ptrace PTRACE_DETACH error");
	else
		fprintf(stderr, "successfully detached from %d\n", g_tracee_pid);
	exit(EXIT_SUCCESS);
}

static int	get_args(int argc, char **av, char ***cmd)
{
	if (argc < 2)
		return (FAILURE);
	if (!strcmp(av[1], "-p") && argc > 2)
		return (atoi(av[2]));
	*cmd = av + 1;
	return (SUCCESS);	}

int	main(int argc, char **argv)
{
	char	**cmd;
	int	ret_value;
	
	if ((ret_value = get_args(argc, argv, &cmd)) == FAILURE)
	{
		fprintf(stderr, "USAGE:\n%s [command]\n%s [-p [pid]]\n", argv[0], argv[0]);
		return (EXIT_FAILURE);
	}
	if (signal(SIGINT, &sig_handler) == SIG_ERR || signal(SIGTERM, &sig_handler) == SIG_ERR)
	{
		warn("signal error");
		return (EXIT_FAILURE);
	}
	if (ret_value == SUCCESS)
		ret_value = trace_by_cmd(cmd);
	else
		ret_value = trace_by_pid(ret_value);
	if (ret_value == FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}