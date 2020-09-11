/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 04:02:15 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/10 06:53:38 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free_error(char **res, int i)
{
	int j;

	j = 0;
	while (j < i)
		free(res[j]);
	free(res);
	return (NULL);
}

char	**allocate_all(char *str, int (*f)(char *, int))
{
	char	**res;
	int		i;
	int		j;

	if (!(res = ft_calloc((count_strs(str, f) + 1) * sizeof(char *), 1)))
		return (NULL);
	i = 0;
	j = -1;
	while (++j <= count_strs(str, f))
	{
		if (!(res[j] = ft_calloc(count_from(str, &i, f) + 1, 1)))
			return (ft_free_error(res, j));
		while (f(str, i))
		{
			if (++j < count_strs(str, f))
				if (!(res[j] = ft_calloc(f(str, i) + 1, 1)))
					return (ft_free_error(res, j));
			i += f(str, i);
		}
	}
	return (res);
}

void	ft_fill_tab(char **res, char *str, int (*f)(char *, int))
{
	int i;
	int j;

	i = 0;
	j = -1;
	while (++j < count_strs(str, f))
	{
		fill_from(res, j, str, &i, f);
		while (f(str, i))
		{
			if (++j < count_strs(str, f))
			{
				res[j][0] = str[i];
				if (f(str, i) == 2)
					res[j][1] = str[i + 1];
				i += f(str, i);
			}
		}
	}
}

void	fill_from(char **res, int k, char *str, int *i, int (*f)(char *, int))
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
		res[k][j++] = str[*i];
		states.escaped = (str[*i] == '\\') ? states.escaped + 1 : 0;
		(*i)++;
	}
	res[k][j++] = 0;
}

char	**ft_split_quotes(char *str, int (*f)(char *, int))
{
	char **res;

	if (!(res = allocate_all(str, f)))
		return (NULL);
	ft_fill_tab(res, str, f);
	res[count_strs(str, f)] = NULL;
	return (res);
}
