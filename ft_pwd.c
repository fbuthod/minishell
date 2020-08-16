# include "minishell.h"

int ft_pwd(char *cmd)
{
	int i;
	char *buf;

	i = 3;
	buf = NULL;
	ft_printf("%s\n", getcwd(buf, 200));
	while (cmd[i] != 0 && cmd[i] != ';')
		i++;
	return (i);
}