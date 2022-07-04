# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/13 17:07:20 by jelarose          #+#    #+#              #
#    Updated: 2020/09/23 14:52:31 by jelarose         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=  	srcs/env.c srcs/env2.c srcs/ft_strcmp.c srcs/get_next_line_utils.c\
			srcs/get_next_line.c srcs/exec.c srcs/utile.c srcs/bultin.c \
			srcs/bultin2.c srcs/fd.c srcs/free.c srcs/parsing.c srcs/ft_split.c\
			srcs/utile2.c srcs/exit_code.c srcs/ft_split2.c srcs/minishell.c\
			srcs/ft_split_save.c srcs/ft_split_string.c srcs/format.c srcs/verif_line.c\
			srcs/var.c srcs/ft_atoi.c srcs/bultin3.c srcs/ret_dir.c srcs/gest_equal.c\
			srcs/fd2.c srcs/utile3.c srcs/free2.c srcs/exec2.c srcs/exec3.c srcs/tilde.c\
			srcs/org.c srcs/echo.c srcs/cd.c srcs/org2.c srcs/verif2.c srcs/format2.c\
			srcs/verif_line2.c srcs/prompt.c

SRCSBONUS	= 

OBJS	= $(SRCS:.c=.o)

NAME	= minishell

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

all:		$(NAME) 

.c.o:
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -Iincludes -o $(NAME)

clean:
			rm -f  $(OBJS)

fclean:	clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
