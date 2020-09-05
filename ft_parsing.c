/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 03:10:28 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/05 08:26:26 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char **ft_remove_void(char **arr)
{
    int i;
    int count;
    char **res;

    i = 0;
    count = 0;
    trim_tab(arr);
    while (arr[i])
        if (ft_strncmp(arr[i++], "", 1))
            count++;
    if (!(res = malloc(sizeof(char *) * (count + 1))))
        return (NULL);    
    res[count] = NULL;
    i = -1;
    count = 0;
    while (arr[++i])
        if (ft_strncmp(arr[i], "", 1))
            res[count++] = ft_strdup(arr[i]);
    free_tab_str(arr);
    return (res);
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
            tmp = ft_remove_void(tmp);
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
