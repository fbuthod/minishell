/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 03:10:28 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/06 07:50:33 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    check_output(char **cmd_lexer, int *i)
{
    int newfdin;
    int newfdout;

    newfdin = 0;
    newfdout = 0;
    while (cmd_lexer[(*i) + 1] != NULL && ft_strncmp(cmd_lexer[(*i)], "|", 2))
    {
        if (ft_strncmp(cmd_lexer[(*i)], ">", 2) == 0) {
            if (newfdout > 0)
                close(newfdout);
            newfdout = open(cmd_lexer[(*i) + 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
            dup2(newfdout, STDOUT_FILENO);
        } else if (ft_strncmp(cmd_lexer[(*i)], ">>", 3) == 0) {
            if (newfdout > 0)
                close(newfdout);
            newfdout = open(cmd_lexer[(*i) + 1], O_CREAT | O_WRONLY | O_APPEND, 0664);
            dup2(newfdout, STDOUT_FILENO);
        } else if (ft_strncmp(cmd_lexer[(*i)], "<", 2) == 0) {
            if (newfdin > 0)
                close(newfdin);
            newfdin = open(cmd_lexer[(*i) + 1], O_RDONLY);
            dup2(newfdin, STDIN_FILENO);
        }
        (*i)++;
    }
}
// ls > tmp;echo next; cat < tmp;rm tmp;exit
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

int parsing(char **cmd_lexer)
{
    int i;
    char *cmd;
    char *path;
    char **tmp;
    int saved_stdout;
    int saved_stdin;
    
    saved_stdout = dup(1);
    saved_stdin = dup(0);
    if (pipe(g_pfd) == -1)
    {
        ft_printf("pipe failed\n");
        return (0);
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
            return (1);
        else if (ft_strncmp("pwd", cmd, 3) == 0)
            ft_pwd(cmd);
        else if (ft_strncmp("cd", cmd, 2) == 0)
            parse_cd(cmd, 2);
        else
        {
            tmp = ft_split_quotes(cmd, is_space);
            // TODO: Escape all whitespaces in args
            tmp = ft_remove_void(tmp);
            if ((path = ft_isinpath(tmp[0])))
                start_process(path, tmp);
            else if (tmp[0][0] == '/')
                start_process(tmp[0], tmp);
            else
                ft_printf("Program not found : [%s]\n", tmp[0]);
            free_tab_str(tmp);
        }
        i++;
        dup2(saved_stdout, 1);
        close(saved_stdout);
        dup2(saved_stdin, 0);
        close(saved_stdin);
    }
    free_tab_str(cmd_lexer);
    return (0);
}
