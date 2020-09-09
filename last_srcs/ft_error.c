# include "minishell.h"

void ft_error(char *cmd)
{
	ft_printf("minishell : command not found: %s\n", cmd);
}