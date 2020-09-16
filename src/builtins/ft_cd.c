/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 01:18:11 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/16 01:34:26 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cd(t_command *cmd)
{
    char *tmp;
    char buff[FILENAME_MAX];

    if (ft_strtablen(cmd->args) == 1)
        chdir(get_env_value("HOME")->value);
    else if (ft_strtablen(cmd->args) == 2 && ft_strlen(cmd->args[1]) <= 4096)
    {
        if (ft_strncmp(cmd->args[1], "~", 2) == 0)
            chdir(get_env_value("HOME")->value);
        else if (cmd->args[1][0] == '.')
        {
            getcwd(buff, FILENAME_MAX);
            tmp = ft_strjoin(buff, &(cmd->args[1][1]));
            if (chdir(tmp))
            {
                ft_printf("minishell: cd: %s: Aucun fichier ou dossier de ce type\n", cmd->args[1]);
                g_last_state = 1;
            }
        }
        else if (chdir(cmd->args[1]))
        {
            ft_printf("minishell: cd: %s: Aucun fichier ou dossier de ce type\n", cmd->args[1]);
            g_last_state = 1;
        }
    }
    else
    {
        if (ft_strlen(cmd->args[1]) > 4096)
            ft_printf("minishell: cd: %s: Nom de fichier trop long", cmd->args[1]);
        else
            ft_printf("minishell: cd: trop d'arguments");
        g_last_state = 1;
    }
    g_last_state = 0;
}