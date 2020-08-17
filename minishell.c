# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include "minishell.h"
# include "get_next_line.h"

int calculate_nbr_cmd(int n, char *cmd)
{
    int i;
    int boolean;

    i = 0;
    boolean = 0;
    while(i < (int)(ft_strlen(cmd)))
    {
        if(boolean == 0)
        {
            if(cmd[i] == ';')
                n++;
        }
        if((cmd[i] == '"') && (boolean == 0))
            boolean = 1;
        else if(cmd[i] == '"' && (boolean == 1))
            boolean = 0;
        i++;
    }
    return (n);
}

char *get_cmd()
{
	char	*line;

	get_next_line(&line);
    return (ft_strdup(line));
}

int main()
{
    char    *cmd;
    int     n;

    n = 1;
    while(1)
    {
        ft_printf("minishell : ");
        cmd = get_cmd();
        n = calculate_nbr_cmd(n, cmd);
        parsing(cmd, n);
        n = 1;
    }
}