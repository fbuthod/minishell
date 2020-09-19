/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:32:51 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 08:21:49 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*new_pair(char *key, char *value)
{
	t_env_var	*node;

	if (!(node = malloc(sizeof(t_env_var))))
		return (NULL);
	node->key = (key) ? ft_strdup(key) : NULL;
	node->value = (value) ? ft_strdup(value) : NULL;
	return (node);
}

t_env_var	*get_env_value(char *key)
{
	t_list		*tmp;

	tmp = g_env;
	while (tmp)
	{
		if (!ft_strncmp(((t_env_var *)tmp->content)->key,
			key, ft_strlen(key) + 1))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void		set_env_value(char *key, char *value)
{
	t_env_var	*node;
	t_list		*new;

	if (get_env_value(key))
	{
		free(get_env_value(key)->value);
		get_env_value(key)->value = value ? ft_strdup(value) : ft_strdup("");
	}
	else
	{
		node = new_pair(key, value);
		new = ft_lstnew(node);
		ft_lstadd_back(&g_env, new);
	}
}

void		remove_env_value(char *key)
{
	if (get_env_value(key))
		ft_lstremove_if(&g_env, key, del, cond);
}

int			init_env(char **envp)
{
	int			i;
	char		**tmp;
	t_env_var	*content;
	t_list		*new;

	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		content = new_pair(tmp[0], tmp[1] ? tmp[1] : "");
		new = ft_lstnew(content);
		ft_lstadd_back(&g_env, new);
		free_tab_str(tmp);
		i++;
	}
	return (0);
}
