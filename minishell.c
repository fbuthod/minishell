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
    printf("nb de commandes : %d\n", n);
    return (n);
}

void parsing(char *cmd, int n)
{
    int i;
    int compt;
    char *buf = NULL;

    i = 0;
    compt = 0;
    while (compt < n)
    {
        while (cmd[i] == ' ' || cmd[i] == ';')
            i++;
        printf("%d\n",ft_strncmp("echo ", &cmd[i], i+5));
        if (ft_strncmp("echo ", &cmd[i], i+5) == 0)-
            i = parse_echo(&cmd[i], i+5);
        else if (ft_strncmp("exit", &cmd[i], i+4) == 0)
            exit(0);
        else if (ft_strncmp("pwd", &cmd[i], i+3) == 0)
            i = ft_printf("%s\n", getcwd(buf, 50));
        else if (ft_strncmp("cd ", &cmd[i], i+3) == 0)
            i = parse_cd(&cmd[i], i+3);
        else
            i = printf("minishell : command not found: %s\n", &cmd[i]);
        compt++;
    }
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