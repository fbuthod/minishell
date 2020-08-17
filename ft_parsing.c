# include "minishell.h"

char *ft_first_test(char *cmd, int *n)
{
    while (cmd[0] == ' ' || cmd[0] == ';')
    {
        if (cmd[0] == ';')
            *n -= 1;
        cmd = ft_substr(cmd, 1, ft_strlen(cmd));
    }
    return (ft_strdup(cmd));
}

char *ft_last_test(char *cmd, int *n)
{
    while (cmd[0] == ' ')
        cmd = ft_substr(cmd, 1, ft_strlen(cmd));
    if (cmd[0] == ';' && cmd[1] == '\0')
        *n -= 1;
    cmd = ft_substr(cmd, 1, ft_strlen(cmd));
    return (ft_strdup(cmd));
}

void parsing(char *cmd, int n)
{
    int i;
    int compt;

    i = 0;
    compt = 0;
    while (compt < n)
    {
        cmd = ft_first_test(cmd, &n);
        if (ft_strncmp("echo ", cmd, 5) == 0)
            i = parse_echo(cmd, 5);
        else if (ft_strncmp("exit", cmd, 4) == 0)
            exit(0);
        else if (ft_strncmp("pwd", cmd, 3) == 0)
            i = ft_pwd(cmd);
        else if (ft_strncmp("cd ", cmd, 3) == 0)
            i = parse_cd(cmd, 3);
        else if (cmd[0] == '\0')
            n = 0;
        else
            i = ft_error(cmd);
        cmd = ft_substr(cmd, i, ft_strlen(cmd));
        cmd = ft_last_test(cmd, &n);
        compt++;
    }
}