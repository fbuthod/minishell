# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbuthod- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/04 12:37:16 by fbuthod-          #+#    #+#              #
#    Updated: 2020/03/13 19:34:57 by fbuthod-         ###   ########lyon.fr    #
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
