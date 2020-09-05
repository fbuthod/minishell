# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include "minishell.h"
# include "get_next_line.h"

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
        i = 0;
        ft_apply_signals(&ft_shell_mode);
        ft_printf("minishell : ");
        if (get_next_line(&cmd) == 0)
        {
            ft_printf("exit\n");
            free(cmd);
            exit(0);
        }
        cmd_split = ft_split_quotes(cmd, is_separator);
        while (cmd_split[i])
        {
            if (ft_strncmp(cmd_split[i], ";", 2) != 0)
            {
                cmd_lexer = ft_lexer(cmd_split[i]);
                if (cmd_lexer)
                    parsing(cmd_lexer);
            }
            i++;
        }
        if (cmd_split)
            free_tab_str(cmd_split);
        free(cmd);
    }
}