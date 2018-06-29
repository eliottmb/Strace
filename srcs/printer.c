/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#include "strace.h"

void	print_int(unsigned long long int register_value)
{
	(void)fprintf(stderr, "%d", (int)register_value);
}

void	print_long(unsigned long long int register_value)
{
	(void)fprintf(stderr, "%ld", (long)register_value);
}

void	print_uint(unsigned long long int register_value)
{
	(void)fprintf(stderr, "%u", (unsigned int)register_value);
}

void	print_ulong(unsigned long long int register_value)
{
	(void)fprintf(stderr, "%lu", (unsigned long)register_value);
}

void	print_pointer(unsigned long long int register_value)
{
	if (register_value == 0)
		fprintf(stderr, "NULL");
	else
		(void)fprintf(stderr, "%p", (void*)register_value);
}
