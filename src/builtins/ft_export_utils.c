/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 08:05:17 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 08:15:18 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(t_list *n1, t_list *n2)
{
	void	*tmp;

	tmp = n1->content;
	n1->content = n2->content;
	n2->content = tmp;
}

void	print_list(t_list *tmp_list)
{
	t_env_var	*tmp_content;

	while (tmp_list)
	{
		tmp_content = (t_env_var *)tmp_list->content;
		if (tmp_content->value)
			ft_printf("declare -X %s=\"%s\"\n", tmp_content->key,
						tmp_content->value);
		else if (tmp_content->key)
			ft_printf("declare -X %s\n", tmp_content->key);
		tmp_list = tmp_list->next;
	}
}

void	modify_var(char *arg)
{
	char	*tmp_value;
	char	*tmp_key;

	if (!(tmp_key = ft_calloc(ft_strchr_chr(arg, '=') - arg + 1, 1)))
	{
		g_last_state = 1;
		return ;
	}
	ft_memcpy(tmp_key, arg, ft_strchr_chr(arg, '=') - arg);
	tmp_value = ft_strdup(ft_strchr_chr(arg, '=') + 1);
	tmp_value = ft_remove_quotes(tmp_value);
	set_env_value(tmp_key, tmp_value);
	free(tmp_value);
	free(tmp_key);
}
