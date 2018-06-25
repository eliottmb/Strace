##
## EPITECH PROJECT, 2018
## strace
## File description:
## Syscall tracer
##

CC	= gcc -I./include/

RM	= rm -f

CFLAGS	+= -W -Wall -Wextra

NAME		= strace

SRCS		= srcs/main.c	\
		  srcs/strace.c

OBJS		= $(SRCS:.c=.o)

RED             =       \033[0;31m
CYAN            =       \033[0;36m
BLUE            =       \033[1;34m
GREEN           =       \033[0;32m
PURPLE          =       \033[0;35m
UNSET           =       \033[0m

all: $(NAME)

$(NAME):	$(OBJS)
		@$(CC) -o $(NAME) $(SRCS) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.cpp.o:
	@$(C) -c $< -o $(CFLAGS) $@
	@printf "$(GREEN)[compiled] $(CYAN) -I./include/ $(BLUE) \
	-W -Wall -Wextra -Werror $(PURPLE)$@\n$(UNSET)"

.PHONY: all clean fclean re
