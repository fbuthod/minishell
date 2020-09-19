/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 00:32:12 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 08:17:46 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
		remove_env_value(cmd->args[i]);
	g_last_state = 0;
}
