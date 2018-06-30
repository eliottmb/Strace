/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

int	sFlag = 0;

extern pid_t	g_pid;

int	createTraced(char **cmd)
{
	if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1)
	{
		quitErr("ptrace PTRACE_TRACEME error");
		return (0);
	}
	if ((execvp(*cmd, cmd)) == -1)
		quitErr("execvp error");
	return (1);
}

static int	tracePid(pid_t pid)
{
	if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1)
		quitErr("ptrace PTRACE_ATTACH error");
	g_pid = pid;
	if (trace(pid) == 0)
		return (0);
	return (1);
}

static int	traceFork(char **cmd)
{
	pid_t	child;

	if ((child = fork()) == -1)
		quitErr("fork error");
	if (child == 0)
	{
		if (createTraced(cmd) == 0)
			exit(EXIT_FAILURE);
	}
	else
	{
		g_pid = child;
		if (trace(child) == 0)
			return (0);
	}
	return (1);
}

static int	checkArgs(int argc, char **av, char ***cmd)
{
	if (argc < 2)
		return (0);
	if (av[1][0] == '-' && av[1][1] == 's')
		sFlag = 1;
	else
		sFlag = 0;
	if (!strcmp(av[1], "-p") && argc > 2)
		return (atoi(av[2]));
	*cmd = av + 1 + sFlag;
	return (1);
}

int	main(int argc, char **argv)
{
	char	**cmd;
	int	to_ret;
	
	sFlag = 0;
	if ((to_ret = checkArgs(argc, argv, &cmd)) == 0)
	{
		fprintf(stderr, "USAGE:\n%s [command]\n%s [-p [pid]]\n", argv[0], argv[0]);
		return (EXIT_FAILURE);
	}
	isGood();
	if (to_ret == 1)
		to_ret = traceFork(cmd);
	else
		to_ret = tracePid(to_ret);
	isGood();
	if (to_ret == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}