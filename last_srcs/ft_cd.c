#include "minishell.h"

int parse_cd(char *cmd, int i)
{
	char *new_char;
	int temp;

	temp = i;
	while (cmd[i] != '\0' && cmd[i] != ';')
		i++;
	new_char = ft_substr(cmd, temp, i - temp);
	//chdir(new_char);
	chdir("/home");
	return (i);
}
