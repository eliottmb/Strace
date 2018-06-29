/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

void	printInt(unsigned long long int register_value)
{
	(void)fprintf(stderr, "%d", (int)register_value);
}

void	printLong(unsigned long long int register_value)
{
	(void)fprintf(stderr, "%ld", (long)register_value);
}

void	printUint(unsigned long long int register_value)
{
	(void)fprintf(stderr, "%u", (unsigned int)register_value);
}

void	printUlong(unsigned long long int register_value)
{
	(void)fprintf(stderr, "%lu", (unsigned long)register_value);
}

void	printPointer(unsigned long long int register_value)
{
	if (register_value == 0)
		fprintf(stderr, "NULL");
	else
		(void)fprintf(stderr, "%p", (void*)register_value);
}
