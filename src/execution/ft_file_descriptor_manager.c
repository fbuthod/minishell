/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_descriptor_manager.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 01:09:58 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/15 05:33:20 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    setup_input(char *cmd_lexer)
{
    dup2(open(cmd_lexer, O_RDONLY), STDIN_FILENO);
}

void    setup_output(char *redirect, char *cmd)
{
    if (ft_strncmp(redirect, ">", 2) == 0) {
        dup2(open(cmd, O_CREAT | O_WRONLY | O_TRUNC, 0664), STDOUT_FILENO);
    } else if (ft_strncmp(redirect, ">>", 3) == 0) {
        dup2(open(cmd, O_CREAT | O_WRONLY | O_APPEND, 0664), STDOUT_FILENO);
    }
}

void    reset_fd(int save[2])
{
    dup2(save[1], 1);
    close(save[1]);
    dup2(save[0], 0);
    close(save[0]);
}
