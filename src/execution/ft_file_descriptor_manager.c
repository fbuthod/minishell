/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_descriptor_manager.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 01:09:58 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 08:43:23 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_input(char *cmd_lexer)
{
	if (g_in != -1)
	{
		close(g_in);
		g_in = -1;
	}
	g_in = open(cmd_lexer, O_RDONLY);
	if (g_in != -1)
		dup2(g_in, STDIN_FILENO);
	else
	{
		ft_printf("minishell: %s: Aucun fichier ou \
					dossier de ce type\n", cmd_lexer);
		g_last_state = 1;
		exit(1);
	}
}

void	setup_output(char *redirect, char *cmd)
{
	if (g_out != -1)
	{
		close(g_out);
		g_out = -1;
	}
	if (ft_strncmp(redirect, ">", 2) == 0)
		g_out = open(cmd, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else if (ft_strncmp(redirect, ">>", 3) == 0)
		g_out = open(cmd, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (g_out != -1)
		dup2(g_out, STDOUT_FILENO);
}

void	reset_fd(int save[2])
{
	dup2(save[1], 1);
	close(save[1]);
	dup2(save[0], 0);
	close(save[0]);
}
