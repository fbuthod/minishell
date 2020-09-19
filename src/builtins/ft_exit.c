/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 01:04:27 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 08:04:38 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean	check_exit(char *cmd_list)
{
	char **tmp;

	tmp = ft_split(cmd_list, ' ');
	trim_tab(tmp);
	tmp = ft_remove_void_elem(tmp);
	if (!(ft_strncmp(tmp[0], "exit", 5)))
		if ((tmp[1] && !tmp[2] && ft_allisdigit(tmp[1])) || !tmp[1])
		{
			ft_free_strs_tab(tmp);
			return (TRUE);
		}
	ft_free_strs_tab(tmp);
	return (FALSE);
}

void		ft_exit(t_command *cmd)
{
	ft_printf("exit\n");
	if (!cmd->args[1])
		g_last_state = 0;
	else if (!ft_allisdigit(cmd->args[1]))
	{
		g_last_state = 1;
		ft_printf("bash: exit: n : argument numérique nécessaire\n");
	}
	else if (cmd->args[2])
	{
		g_last_state = 1;
		ft_printf("bash: exit: trop d'arguments\n");
		exit(1);
	}
	else
		g_last_state = ft_atoi(cmd->args[1]);
}
