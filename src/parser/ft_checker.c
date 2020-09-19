/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 10:57:53 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 10:58:25 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_redirection(const char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '>')
		return (2);
	else if (str[i] == '>' || str[i] == '<')
		return (1);
	return (0);
}

int		is_spaceredirection(const char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '>')
		return (2);
	else if (str[i] == '>' || str[i] == '<' || str[i] == ' ')
		return (1);
	return (0);
}

int		is_separator(const char *str, int i)
{
	if (str[i] == ';')
		return (1);
	return (0);
}

int		is_pipe(const char *str, int i)
{
	if (str[i] == '|')
		return (1);
	return (0);
}

int		is_equal(const char *str, int i)
{
	if (str[i] == '=')
		return (1);
	return (0);
}
