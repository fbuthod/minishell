# include "minishell.h"

int ft_error(char *cmd)
{
	int i;

	i = 0;
	ft_printf("minishell : command not found: ");
	while (cmd[i] != 0 && cmd[i] != ';')
	{
		if (cmd[i] != '"' && cmd[i] != '\'')
			ft_printf("%c", cmd[i]);
		i++;
	}
	ft_printf("\n");
	return (i);
}