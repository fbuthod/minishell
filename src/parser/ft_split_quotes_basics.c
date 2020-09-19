/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes_basics.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 04:05:16 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 10:58:22 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_space(const char *str, int i)
{
	if (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' ||
		str[i] == '\v' || str[i] == '\n' || str[i] == '\f')
		return (1);
	return (0);
}

int		is_pipe_redirection(const char *str, int i)
{
	if (str[i] == '>' && str[i + 1] == '>')
		return (2);
	else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (1);
	return (0);
}

int		check_quotes(t_split_quotes *states, const char *str, int i)
{
	if (!(states->escaped % 2) && str[i] == '\"' && !states->s_quote)
		states->d_quote = (states->d_quote) ? 0 : 1;
	else if (!(states->escaped % 2) && str[i] == '\'' && !states->d_quote)
		states->s_quote = (states->s_quote) ? 0 : 1;
	return (1);
}

int		count_strs(const char *str, int (*f)(const char *, int))
{
	t_split_quotes	states;
	int				res;
	int				i;

	i = -1;
	res = (ft_strlen(str) > 0) ? 1 : 0;
	states.s_quote = 0;
	states.d_quote = 0;
	states.escaped = 0;
	while (str[++i] && check_quotes(&states, str, i))
	{
		if (!states.s_quote && !states.d_quote)
			while (f(str, i) > 0 && ++res)
			{
				i += f(str, i);
				if (str[i] && !f(str, i))
					res++;
				if (str[i])
					check_quotes(&states, str, i);
			}
		if (!str[i])
			break ;
		states.escaped = (str[i] == '\\') ? states.escaped + 1 : 0;
	}
	return (res);
}

int		count_from(char *str, int *i, int (*f)(const char *, int))
{
	t_split_quotes	states;
	int				j;

	j = 0;
	states.d_quote = 0;
	states.s_quote = 0;
	states.escaped = 0;
	while (str[*i])
	{
		check_quotes(&states, str, *i);
		if (!states.d_quote && !states.s_quote && f(str, *i))
			break ;
		j++;
		states.escaped = (str[*i] == '\\') ? states.escaped + 1 : 0;
		(*i)++;
	}
	return (j);
}
