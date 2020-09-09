/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 22:56:23 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/08 22:58:40 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_echo(t_cmd *cmd, t_builtin *builtin)
{
	int	i;
	int	option;

	(void)cmd;
	i = 1;
	option = 0;
	while (builtin->argv[i])
	{
		if (ft_strcmp(builtin->argv[i], "-n") == 0)
			option = 1;
		else
		{
			if (option > 0)
				option += 1;
			if (builtin->argv[i])
				ft_printf("%s", builtin->argv[i]);
			if (builtin->argv[i + 1])
				ft_printf(" ");
		}
		i++;
	}
	if (option != 1)
		ft_printf("\n");
	return (0);
}