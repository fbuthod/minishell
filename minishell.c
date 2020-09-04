# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include "minishell.h"
# include "get_next_line.h"

char *get_cmd()
{
	char	*line;

	get_next_line(&line);
    return (ft_strdup(line));
}

int main(int ac, char **av, char *envp[])
{
    char    *cmd;
    char    **cmd_split;
    char    **cmd_lexer;
    int     i;

    ac = 0;
    av = 0;
    g_env = envp;
    while(1)
    {
        ft_printf("minishell : ");
        cmd = get_cmd();
        cmd_split = ft_split_quotes(cmd, is_separator);
        i = 0;
        while (cmd_split[i])
        {
            if (ft_strncmp(cmd_split[i], ";", 2) != 0)
            {
                dprintf(1, "{%d : %s}\n", i, cmd_split[i]);
                cmd_lexer = ft_lexer(cmd_split[i]);
                if (cmd_lexer)
                    parsing(cmd_lexer);
            }
            i++;
        }
        if (cmd_split)
            free_tab_str(cmd_split);
    }
}