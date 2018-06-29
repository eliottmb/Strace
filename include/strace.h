/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#ifndef		__STRACE_H__
# define	__STRACE_H__

/*
** INCLUDES
*/

# include <err.h>
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ptrace.h>
# include <sys/types.h>
# include <sys/user.h>
# include <sys/wait.h>
# include <unistd.h>

/*
** DEFINES
*/

# define FAILURE 0
# define SUCCESS 1
# define EXIT 2

# define MAX_SYSCALL 313
# define SYSCALL_OPCODE 0x050f

/*
** STRUCTS
*/

typedef struct	s_prototype
{
  char		*name;
  int		nb_params;
  char		*params[6];
  char		*ret_type;
}		t_prototype;

typedef struct	s_types
{
  char		*name;
  void		(*print_fct)(unsigned long long int register_value);
}		t_types;

/*
** main.c
*/

void	handle_exit(int *status);

/*
** launch_child.c
*/
int	createChild(char **cmd);

/*
** print_syscalls.c
*/
void	printAllArgs(int syscall_number, struct user_regs_struct *registers);
void	printRet(int nb_syscall,
			   char *type, struct user_regs_struct *registers);
int	printCall(int syscall_number, struct user_regs_struct *registers);

/*
** print_types.c
*/
void	printInt(unsigned long long int register_value);
void	printLong(unsigned long long int register_value);
void	printUint(unsigned long long int register_value);
void	printUlong(unsigned long long int register_value);
void	printPointer(unsigned long long int register_value);

/*
** print_types2.c
*/
void	printString(unsigned long long int register_value);
void	printStringTab(unsigned long long int register_value);
void	printUnimplemented(unsigned long long int register_value);
void	printNothing(unsigned long long int register_value);

/*
** trace.c
*/
int	trace(pid_t pid);

#endif /* !STRACE_H_ */
