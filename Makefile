# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 12:37:16 by fbuthod-          #+#    #+#              #
#    Updated: 2020/09/16 14:12:53 by gbaud            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                    VARIABLES                                 #
# **************************************************************************** #

CC=clang

CFLAGS=-Wall -Wextra -Werror -g3 -fsanitize=address -I ./includes/

NAME=minishell

SRCS	=	./src/main.c									\
			./src/env/ft_env_manager.c						\
			./src/env/ft_replace_env.c						\
			./src/execution/ft_exec.c						\
			./src/execution/ft_commands_manager.c			\
			./src/execution/ft_file_descriptor_manager.c 	\
			./src/parser/ft_get_command_list.c				\
			./src/parser/ft_split_quotes.c					\
			./src/parser/ft_split_quotes_basics.c			\
			./src/parser/ft_lexer.c							\
			./src/builtins/ft_env.c							\
			./src/builtins/ft_unset.c						\
			./src/builtins/ft_export.c						\
			./src/builtins/ft_pwd.c							\
			./src/builtins/ft_exit.c						\
			./src/builtins/ft_echo.c						\
			./src/builtins/ft_cd.c							\
			./src/utils/ft_signals.c


LIBFT	=	./libft/libft.a

HEADER	=	includes/minishell.h

OBJS	=	$(SRCS:.c=.o)

RM		=	rm -f

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

%.c%.o:
				$(CC) $(CFLAGS) -c $< -o $@

all:            $(NAME)

$(OBJS):        $(INC)

lib:
				$(MAKE) -C libft

$(NAME):        $(OBJS) $(HEADER) lib
				$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
				$(RM) $(OBJS)
				cd libft && make clean

fclean:         clean
				$(RM) $(NAME)
				cd libft && make fclean

re:             fclean all

.PHONY: all bonus clean fclean re lib