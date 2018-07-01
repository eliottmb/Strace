/*
** EPITECH PROJECT, 2018
** strace
** File description:
** Syscall tracer
*/

#ifndef		__STRACE_H__
# define	__STRACE_H__

# include <sys/ptrace.h>
# include <err.h>
# include <sys/user.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>

extern int	sFlag;

typedef struct	s_calls
{
	char	*name;
	int	nb_params;
	char	*params[6];
	char	*ret_type;
}		t_calls;

typedef struct	s_fctTab
{
	char	*name;
	void	(*sortFct)(unsigned long long int regs);
}		t_fctTab;

unsigned long long	lowRegs(int nb_args, struct user_regs_struct *regs);
unsigned long long	mediumRegs(int nb_args, struct user_regs_struct *regs);
unsigned long long	highRegs(int nb_args, struct user_regs_struct *regs);
void			sortNothing(unsigned long long int regsVal);
void			checkStatus(int status);
int			checkCall();
void			checkRegs(struct user_regs_struct *regs);
void			checkParamAdd(void *ptr);
void			isGood();
unsigned long long int	getGoodRegister(int nb_args, struct user_regs_struct *regs);
void			sortArg(char *type, int nb_args, struct user_regs_struct *regs);
void			sortRet(int nb_syscall, char *type, struct user_regs_struct *regs);
void			sortAllArgs(int nb_syscall, struct user_regs_struct *regs);
int			sortCall(int nb_syscall, struct user_regs_struct *regs);
void			sortChar(char c);
void			sortStringPtr(unsigned long long int regsVal);
void			sortString(unsigned long long int regsVal);
void			sortStringTab(unsigned long long int regsVal);
void			sortNope(unsigned long long int regsVal);
void			sortInt(unsigned long long int regs);
void			sortLong(unsigned long long int regs);
void			sortUint(unsigned long long int regs);
void			sortUlong(unsigned long long int regs);
void			sortPointer(unsigned long long int regs);
void			quitErr(char *str);
int			next(pid_t pid, int *status);
int			getCall(struct user_regs_struct *regs, pid_t pid, int *status);
int			getRegs(struct user_regs_struct *regs, pid_t pid, int *status);
int			trace(pid_t pid);

#endif /* __STRACE_H__ */
