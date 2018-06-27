/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "strace.h"

void help(char *s)
{
  printf("Usage: %s [-s] [-p <PID>|<command>]\n", s);
  exit(0);
}

int	main(int argc, char **argv)
{
	pid_t pid;
	
	if (argc == 1)
		help(argv[0]);
	if ((pid = fork()) == 0)
		return (forked(argc - 1, argv + 1));
	else
    		return (my_trace(pid));
	return (0);
}
