# include "minishell.h"

void    check_output(char **cmd_lexer, int *i)
{
    int fd;

    fd = 1;
    while (cmd_lexer[(*i) + 1] != NULL && ft_strncmp(cmd_lexer[(*i)], "|", 2))
    {
        if (ft_strncmp(cmd_lexer[(*i)], ">", 2) == 0) {
            fd = open(cmd_lexer[(*i) + 1], O_TRUNC | O_WRONLY | O_CREAT, 0664);
            ft_printf("Last open TRUNC : %s\n", cmd_lexer[(*i) + 1]);
        } else if (ft_strncmp(cmd_lexer[(*i)], ">>", 3) == 0) {
            fd = open(cmd_lexer[(*i) + 1], O_APPEND | O_WRONLY | O_CREAT, 0664);
            ft_printf("Last open APPEMD : %s\n", cmd_lexer[(*i) + 1]);
        }
        (*i)++;
    }
}

void parsing(char **cmd_lexer)
{
    int i;
    char *cmd;
    char *path;
    char **tmp;

    if (pipe(g_pfd) == -1)
    {
        ft_printf("pipe failed\n");
        return ;
    }
    i = 0;
    while (cmd_lexer[i] != NULL)
    {
        cmd = cmd_lexer[i];
        check_output(cmd_lexer, &i);

        dprintf(1, "command:[%s] execute into:[%s]\n",
                cmd, (cmd_lexer[i + 1]) ? cmd_lexer[i - 1] : cmd_lexer[i]);
        if (ft_strncmp("export", cmd, 6) == 0)
            ft_export(cmd, 6);
        else if (ft_strncmp("unset ", cmd, 6) == 0)
            ft_unset(cmd, 7);
        else if (ft_strncmp("echo ", cmd, 5) == 0)
            parse_echo(cmd, 5);
        else if (ft_strncmp("exit", cmd, 4) == 0)
            exit(0);
        else if (ft_strncmp("pwd", cmd, 3) == 0)
            ft_pwd(cmd);
        else if (ft_strncmp("cd", cmd, 2) == 0)
            parse_cd(cmd, 2);
        else
        {
            tmp = ft_split_quotes(cmd, is_space);
            if ((path = ft_isinpath(tmp[0])))
                start_process(path, tmp);
            else if (tmp[0][0] == '/')
                start_process(tmp[0], tmp);
            free_tab_str(tmp);
        }
        i++;
    }
    free_tab_str(cmd_lexer);
}

/*

TODO : remove space in tmp tab

*/