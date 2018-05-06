##
## EPITECH PROJECT, 2018
## Philosopher
## File description:
## makefile
##

RM	=	rm -f

CC	=	gcc

LDFLAGS	=	-pthread

DIR	=	src

CFLAGS	=	-I.
CFLAGS	+=	-W -Wall -Werror -Wextra -I ./include

SRCS	=	$(DIR)/main.c	\
		$(DIR)/check_argv.c	\
		$(DIR)/philosopher.c	\
		$(DIR)/state_philo.c

OBJS	=	$(SRCS:.c=.o)

NAME	=	philo

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) -L./lib -lriceferee

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	all clean

.PHONY:	all clean fclean re
