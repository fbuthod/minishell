/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 01:12:31 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 08:17:18 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_command *cmd)
{
	t_boolean	n;
	int			i;

	i = 0;
	n = FALSE;
	while (cmd->args[++i])
	{
		if (!ft_strncmp(cmd->args[i], "-n", 3))
			n = TRUE;
		else
		{
			ft_printf("%s", cmd->args[i]);
			if (cmd->args[i + 1])
				ft_printf(" ");
		}
	}
	if (!n)
		ft_printf("\n");
	g_last_state = 0;
}
