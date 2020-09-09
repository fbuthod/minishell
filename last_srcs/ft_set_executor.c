/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 05:57:52 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/08 23:02:39 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_from_path(char *command_label, char **command_args, int cont, int (*f)(char *, char **, int))
{
    char *path;

    if ((path = ft_isinpath(command_label)))
    {
        f(path, command_args, cont);
        free(path);
    }
    else if (command_label[0] == '/')
        f(command_label, command_args, cont);
    else
        ft_printf("Program not found : [%s]\n", command_label);
}

void    setup_param(char **cmd_label, char ***cmd_args, char *cmd)
{
    *cmd_args = command_from_string(cmd);
    *cmd_label = ft_strdup(*cmd_args[0]);
}

int exec_correct(char *cmd, int cont, int (*f)(char *, char **, int))
{
    int ret;
    char *command_label;
    char **command_args;

    ret = 0;
    setup_param(&command_label, &command_args, cmd);
    if (!ft_strncmp("env", command_label, 4))
        /*ft_export(command_args[0], 6)*/;
    else if (!ft_strncmp("export", command_label, 7))
        /*ft_export(command_args[0], 6)*/;
    else if (!ft_strncmp("unset", command_label, 6))
        /*ft_unset(command_args[0], 7)*/;
    else if (!ft_strncmp("echo", command_label, 5))
        /*parse_echo(command_args[0], 5)*/;
    else if (!ft_strncmp("exit", command_label, 5))
        ret = 1;
    else if (!ft_strncmp("pwd", command_label, 4))
        /*ft_pwd(command_args[0])*/;
    else if (!ft_strncmp("cd", command_label, 3))
        /*parse_cd(command_args[0], 2)*/;
    else 
        exec_from_path(command_label, command_args, cont, f);
    free_tab_str(command_args);
    free(command_label);
    return (ret);
}
