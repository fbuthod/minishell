#include "minishell.h"

/*int parse_echo(char *cmd, int i)
{
	int res;
	
	if (ft_strncmp("-n ", &cmd[i], 3) == 0)
        res = ft_printf("%s", ft_substr(cmd, i+3, ft_strlen(cmd))) + 4 ;
	else
		res = ft_printf("%s\n", ft_substr(cmd, i, ft_strlen(cmd)));
	return (i + res - 1);
}*/

int parse_echo(char *cmd, int i)
{
	int compt;
	int res;

	compt = 0;
	res = 0;
	while (cmd[i] != ';' && cmd[i] != '\0')
	{
		if (ft_strncmp("-n ", &cmd[i], i+3) == 0)
		{
			res = 1;
			i += 3;
		}
		ft_printf("%c", cmd[i]);
		compt++;
		i++;
	}
	while (cmd[i] == ' ')
		i++;
	if (res == 0)
		ft_printf("\n");
	return (i);
}