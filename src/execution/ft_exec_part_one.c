/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_part_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 11:24:21 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 11:26:04 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*apply_escape(char *str)
{
	int		i;
	int		j;
	int		count;
	char	*res;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == '\\' && i++)
			count++;
	if (!(res = ft_calloc(ft_strlen(str) - count + 1, 1)))
		return (NULL);
	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] == '\\' && i++)
			res[++j] = str[i];
		else
			res[++j] = str[i];
	free(str);
	return (res);
}

int				fill_command(t_command *cmd_s, char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	if (!(cmd_s->cmd = ft_calloc(i + 1, 1)))
		return (-1);
	ft_memcpy(cmd_s->cmd, cmd, i);
	return (i);
}

char			**ft_remove_void_elem(char **args)
{
	char	**res;
	int		count;
	int		i;
	int		j;

	i = -1;
	count = 0;
	while (args[++i])
		if (!is_str(args[i], ""))
			count++;
	if (!(res = ft_calloc(count + 1, sizeof(char *))))
	{
		free_tab_str(args);
		return (NULL);
	}
	i = -1;
	j = 0;
	while (args[++i])
		if (!is_str(args[i], ""))
		{
			res[j] = ft_strdup(args[i]);
			j++;
		}
	ft_free_strs_tab(args);
	return (res);
}

t_boolean		check_valid_command(char **cmd)
{
	int i;

	i = 0;
	if (cmd && is_redirection(cmd[0], 0))
		return (FALSE);
	if (cmd)
		while (cmd[i + 1])
		{
			if (is_redirection(cmd[i], 0) && is_redirection(cmd[i + 1], 0))
				return (FALSE);
			i++;
		}
	if (cmd && is_redirection(cmd[i], 0))
		return (FALSE);
	return (TRUE);
}

char			*ft_remove_quotes(char *arg)
{
	t_split_quotes	state;
	char			*tmp;
	int				i;

	i = -1;
	state.d_quote = 0;
	state.s_quote = 0;
	state.escaped = 0;
	while (((arg[++i] == '\"' && arg[ft_strlen(arg) - i - 1] == '\"') ||
	(!state.d_quote && arg[i] == '\'' && arg[ft_strlen(arg) - i - 1] == '\'')))
		check_quotes(&state, arg, i);
	if ((i >= (int)ft_strlen(arg) - i - 1))
		tmp = ft_strdup("");
	else
	{
		if (!(tmp = ft_calloc(ft_strlen(arg) - i, 1)))
		{
			free(arg);
			return (NULL);
		}
		ft_memcpy(tmp, &arg[i], ft_strlen(arg) - i * 2);
	}
	free(arg);
	return (tmp);
}
