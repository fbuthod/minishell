/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_command_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 09:05:19 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 10:44:02 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_remove_void(char **arr)
{
	int		i;
	int		count;
	char	**res;

	i = 0;
	count = 0;
	trim_tab(arr);
	while (arr[i])
		if (ft_strncmp(arr[i++], "", 1))
			count++;
	if (!(res = malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	res[count] = NULL;
	i = -1;
	count = 0;
	while (arr[++i])
		if (ft_strncmp(arr[i], "", 1))
			res[count++] = ft_strdup(arr[i]);
	free_tab_str(arr);
	return (res);
}

char		**get_args(char *cmd)
{
	char **res;

	if (!(res = ft_split_quotes(cmd, is_space)))
		return (NULL);
	if (!(res = ft_remove_void(res)))
		return (NULL);
	return (res);
}

t_command	*get_command_from_string(char *cmd, char *next)
{
	t_command	*command;

	if (!(command = (t_command *)malloc(sizeof(t_command))))
		return (NULL);
	if (!(command->args = get_args(cmd)))
	{
		free(command);
		return (NULL);
	}
	command->cmd = command->args ? command->args[0] : NULL;
	command->next = next;
	return (command);
}

t_list		*get_from(char **arr)
{
	t_list		*head;
	t_list		*n;
	t_command	*tmp;
	int			i;

	i = 0;
	head = NULL;
	while (arr[i])
	{
		tmp = get_command_from_string(arr[i], arr[i + 1]);
		n = ft_lstnew(tmp);
		ft_lstadd_back(&head, n);
		i += arr[i + 1] ? 2 : 1;
	}
	return (head);
}
