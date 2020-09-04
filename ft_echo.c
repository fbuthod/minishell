#include "minishell.h"

int quote_function(char *cmd)
{
    int i;

    i = 1;
    while(cmd[i] != '"' || cmd[i] == '\0')
    {
		if (cmd[i] == '\\')
		{
			if (cmd[i + 1] == 'n')
			{
				ft_printf("\n");
				i += 2;
			}
		}
		ft_printf("%c", cmd[i]);
        i++;
    }
	i++;
    return (i);
}

int parse_echo(char *cmd, int i)
{
	int compt;
	int res;

	compt = 0;
	res = 0;
	while (cmd[i] == ' ')
        cmd = ft_substr(cmd, 1, ft_strlen(cmd));
	while (cmd[i] != ';' && cmd[i] != '\0')
	{
		if (cmd[i] == '$')
			i += ft_env(&cmd[i+1]);
		if (ft_strncmp("-n ", &cmd[i], i+3) == 0)
		{
			res = 1;
			i += 3;
		}
		if (cmd[i] == '"')
			i += quote_function(&cmd[i]);
		while (cmd[i] == ' ' && cmd[i+1] == ' ')
		{
			cmd = ft_substr(cmd, 1, ft_strlen(cmd));
			compt++;
		}
		if (cmd[i] == '\\')
			i++;
		else if (cmd[i] != ';')
			ft_printf("%c", cmd[i++]);
	}
	while (cmd[i] == ' ')
		i++;
	if (res == 0)
		ft_printf("\n");
	return (i + compt);
}