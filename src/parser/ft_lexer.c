/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 05:05:17 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/16 16:05:02 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_tab_str(char **res)
{
	int i;

	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
	res = NULL;
	return (res);
}

int		tab_len(char **res)
{
	int i;

	i = 0;
	while (res[i])
		i++;
	return (i);
}

char **trim_tab(char **res)
{
	int i;
	char *tmp;

	i = 0;
	while (i < tab_len(res))
	{
		tmp = ft_strtrim(res[i], " \t\v\r\n");
		free(res[i]);
		res[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	return (res);
}

char	**ft_lexer(char *str, int (*f)(const char *, int))
{
	char **res;
    int len;
    int i;

    res = ft_split_quotes(str, f);
    len = tab_len(res);
	i = -1;
	trim_tab(res);
	while (res != NULL && ++i < len)
		if (ft_strncmp(res[i], "", 1) == 0)
			free_tab_str(res);
	if (res != NULL && f(res[len - 1], 0))
		free_tab_str(res);
	i = -1;
	while (res != NULL && ++i < len - 1)
		if (f(res[i], 0) && f(res[i + 1], 0))
			free_tab_str(res);
	if (res == NULL)
		ft_printf("parsing error\n");
	return (res);
}
