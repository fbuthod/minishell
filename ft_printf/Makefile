# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksam <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/15 10:59:50 by ksam              #+#    #+#              #
#    Updated: 2020/03/06 01:11:54 by ksam             ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                    VARIABLES                                 #
# **************************************************************************** #

NAME        = libftprintf.a

HEADER      = include/libftprintf.h

LIB         = libft.a

LIBS        = libft/libft.a

SRCS		= src/convert_c.c \
			  src/convert_di.c \
			  src/convert_p.c \
			  src/convert_percent.c \
			  src/convert_s.c \
			  src/convert_u.c \
			  src/convert_xx.c \
			  src/ft_convert_part_one_n_two.c \
			  src/ft_convert_utils.c \
			  src/ft_convert.c \
			  src/ft_itoa_base_printf.c \
			  src/ft_precision.c \
			  src/ft_printf_utils.c \
			  src/ft_printf.c \
			  src/ft_width_utils.c \
			  src/ft_width.c \
			  src/struct_initialize.c

OBJS        = $(SRCS:.c=.o)

CC          = gcc

RM          = rm -f

CFLAGS      = -Wall -Wextra -Werror -g3 -Iinclude -Ilibft

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all         : $(LIB) $(NAME)

$(NAME)     : $(OBJS) $(HEADER)
			cp libft/libft.a ./$(NAME)
			ar rc $(NAME) $(OBJS)

$(LIB)      :       
			$(MAKE) -C libft all

%.o 		: %.c $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $@

clean       :
			$(MAKE) -C libft clean
			$(RM) $(OBJS)

fclean      : clean
			$(RM) $(LIBS)
			$(RM) $(NAME)

re          : fclean all

.PHONY      : clean fclean all re
