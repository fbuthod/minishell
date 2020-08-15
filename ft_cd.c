#include "minishell.h"

int parse_cd(char *cmd, int i)
{
	chdir(&cmd[i]);
	return (i + ft_strlen(&cmd[i]));
}