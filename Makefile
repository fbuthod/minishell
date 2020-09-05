# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 12:37:16 by fbuthod-          #+#    #+#              #
#    Updated: 2020/09/04 11:53:34 by gbaud            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                    VARIABLES                                 #
# **************************************************************************** #

default: all

OS = $(shell uname)

NAME    =	minishell

HEADER	=	includes/minishell.h

PRINTF	=	libftprintf.a

PRINTFS	=	ft_printf/libftprintf.a

LIBFTS	=	ft_printf/libft/libft.a

SRCS	=	minishell.c				\
			get_next_line.c			\
			get_next_line_utils.c	\
			ft_echo.c				\
			ft_cd.c					\
			ft_error.c				\
			ft_pwd.c				\
			ft_parsing.c			\
			ft_split_quotes.c		\
			ft_split_quotes_basics.c\
			ft_lexer.c				\
			ft_executor.c			\
			ft_env.c				\
			ft_signals.c

OBJS	=	$(SRCS:.c=.o)

CC 		=	clang

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -g3 -Iincludes/ -Ift_printf/include/ -Ift_print/libft/


# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all		:	$(NAME) $(HEADER)

%.o		:	%.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	:	$(PRINTF) $(OBJS) $(HEADER)
			$(CC) $(CFLAGS) -o $@ $(SRCS) $(PRINTFS) -Lft_printf

$(PRINTF)	:
			$(MAKE) -C ft_printf all

clean	:
			$(MAKE) -C ft_printf $@
			$(RM) $(OBJS)

fclean	: 	clean
			$(RM) $(LIBFTS)
			$(RM) $(PRINTFS)
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	clean fclean all re
