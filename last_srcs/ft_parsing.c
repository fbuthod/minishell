/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 03:10:28 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/08 09:02:53 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    update_in_fd(char *cmd_lexer)
{
    int newfdin;

    ft_printf("IN:[%s]\n", cmd_lexer);
    newfdin = open(cmd_lexer, O_RDONLY);
    dup2(newfdin, STDIN_FILENO);
}

void    update_out_fd(char *redirect, char *cmd_lexer)
{
    int newfdout;

    ft_printf("OUT:[%s]=>[%s]\n", cmd_lexer, redirect);
    if (ft_strncmp(redirect, ">", 2) == 0) {
        newfdout = open(cmd_lexer, O_CREAT | O_WRONLY | O_TRUNC, 0664);
        dup2(newfdout, STDOUT_FILENO);
    } else if (ft_strncmp(redirect, ">>", 3) == 0) {
        newfdout = open(cmd_lexer, O_CREAT | O_WRONLY | O_APPEND, 0664);
        dup2(newfdout, STDOUT_FILENO);
    }
}

// ls > tmp;echo next; cat < tmp;rm tmp;exit

void    reset_fd(int save[2])
{
    dup2(save[1], 1);
    close(save[1]);
    dup2(save[0], 0);
    close(save[0]);
}

int parsing(char **cmd_lexer)
{
    int i;
    int j;
    int save[2];

    i = -1;
    save[0] = dup(0);
    save[1] = dup(1);
    while (cmd_lexer[++i])
        if (!cmd_lexer[i + 1] || !ft_strncmp(cmd_lexer[i + 1], "|", 2))
        {
            if (exec_correct(cmd_lexer[i], (cmd_lexer[i + 1] != NULL) ? 1 : 0, start_process))
                return (1);
        }
        else if (!ft_strncmp(cmd_lexer[i + 1], ">", 2) || !ft_strncmp(cmd_lexer[i + 1], ">>", 3))
        {
            j = i;
            while (cmd_lexer[j + 1] != NULL &&
                    (!ft_strncmp(cmd_lexer[j + 1], ">", 2) || !ft_strncmp(cmd_lexer[j + 1], ">>", 3) || !ft_strncmp(cmd_lexer[j + 1], "<", 2)))
            {
                if (!ft_strncmp(cmd_lexer[i + 1], "<", 2))
                    update_in_fd(cmd_lexer[j + 2]);
                else
                    update_out_fd(cmd_lexer[j + 1], cmd_lexer[j + 2]);
                j += 2;
            }
            if (exec_correct(cmd_lexer[i], 0, simple_exec))
                return (1);
            i = j;
            reset_fd(save);
        }
    return (0);
}

/*
int parsing(char **cmd_lexer)
{
    int i;
    char **cmd;
    char *path;
    int saved_stdout;
    int saved_stdin;
    
    saved_stdout = dup(1);
    saved_stdin = dup(0);
    i = 0;
    while (cmd_lexer[i] != NULL)
    {
        // TODO: Change all builtins work
        cmd = command_from_string(cmd_lexer[i]);
        check_output(cmd_lexer, &i);
        if (ft_strncmp("export", cmd[0], 6) == 0)
            ft_export(cmd[0], 6);
        else if (ft_strncmp("unset ", cmd[0], 6) == 0)
            ft_unset(cmd[0], 7);
        else if (ft_strncmp("echo ", cmd[0], 5) == 0)
            parse_echo(cmd[0], 5);
        else if (ft_strncmp("exit", cmd[0], 4) == 0)
            return (1);
        else if (ft_strncmp("pwd", cmd[0], 3) == 0)
            ft_pwd(cmd[0]);
        else if (ft_strncmp("cd", cmd[0], 2) == 0)
            parse_cd(cmd[0], 2);
        else
        {
            if ((path = ft_isinpath(cmd[0])))
                start_process(path, cmd);
            else if (cmd[0][0] == '/')
                start_process(cmd[0], cmd);
            else
                ft_printf("Program not found : [%s]\n", cmd[0]);
            free_tab_str(cmd);
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
*/