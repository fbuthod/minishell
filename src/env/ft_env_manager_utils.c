/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_manager_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 08:20:58 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 08:23:09 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cond(void *key, void *content)
{
	t_env_var	*tmp;

	tmp = (t_env_var *)content;
	if (tmp->key != NULL && !ft_strncmp(tmp->key,
		(char *)key, ft_strlen((char *)key) + 1))
		return (TRUE);
	return (FALSE);
}

void		del(void *content)
{
	t_env_var	*tmp;

	tmp = (t_env_var *)content;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void		print(void *content)
{
	t_env_var	*tmp;

	tmp = (t_env_var *)content;
	ft_printf("[%s] => [%s]\n", tmp->key, tmp->value);
}

char		**env_to_tab(void)
{
	int			i;
	char		**tmp;
	t_list		*head;
	t_env_var	*env;

	if (!(tmp = ft_calloc(ft_lstsize(g_env), sizeof(char *))))
		return (NULL);
	head = g_env;
	i = 0;
	while (head)
	{
		env = (t_env_var *)head->content;
		if (env->key)
		{
			tmp[i] = ft_strjoin(env->key, "=");
			if (env->value)
				tmp[i] = ft_strfjoin(tmp[i], env->value, 1);
			i++;
		}
		head = head->next;
	}
	return (tmp);
}
