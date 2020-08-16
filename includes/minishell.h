#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../ft_printf/libft/libft.h"
# include "../ft_printf/include/libftprintf.h"

int	ft_read_line(int *get, char **line);
char *ft_strdup(const char *s1);
int parse_echo(char *cmd, int i);
int parse_cd(char *cmd, int i);
int ft_error(char *cmd);
int ft_pwd(char *cmd);

#endif