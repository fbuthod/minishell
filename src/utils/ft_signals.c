/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 09:35:24 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/16 11:54:04 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_apply_signals(void (*signal_func)(int))
{
	signal(SIGINT, signal_func);
	signal(SIGQUIT, signal_func);
}

void	ft_shell_mode(int code)
{
	int pid;

	pid = code;
	if (code == 2)
		ft_printf("\n%sminishell : \033[0m",
					g_last_state ? "\033[1;31m" : "\033[1;32m");
	else if (code == 3)
		kill(pid, code);
}