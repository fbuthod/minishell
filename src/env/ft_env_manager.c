/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:32:51 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/09 08:47:57 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var *new_pair(char *key, char *value)
{
    t_env_var *node;

    if (!(node = malloc(sizeof(t_env_var))))
        return (NULL);
    node->key = (key) ? ft_strdup(key) : NULL;
    node->value = (value) ? ft_strdup(value) : NULL;
    return (node);
}

t_env_var    *get_env_value(char *key)
{
    t_list *tmp;

    tmp = g_env;
    while (((t_env_var *)tmp->content)->key)
    {
        if (!ft_strncmp(((t_env_var *)tmp->content)->key, key, ft_strlen(key) + 1))
            return (tmp->content);
        tmp = tmp->next;
    }
    return (tmp->content);
}

void    set_env_value(char *key, char *value)
{
    t_env_var *node;
    t_list *new;

    if (get_env_value(key))
    {
        free(get_env_value(key)->value);
        get_env_value(key)->value = ft_strdup(value);
    }
    else
    {
        node = new_pair(key, value);
        new = ft_lstnew(node);
        ft_lstadd_back(&g_env, new);
    }
}

int    init_env(char **envp)
{
    int i;
    char **tmp;
    t_env_var *content;
    t_list *new;

    i = 0;
    while (envp[i])
    {
        tmp = ft_split(envp[i], '=');
        content = new_pair(tmp[0], tmp[1]);
        new = ft_lstnew(content);
        ft_lstadd_back(&g_env, new);
        //ft_printf("[%s] : [%s]\n", content->key, content->value);
        free_tab_str(tmp);
        i++;
    }
    content = new_pair(NULL, NULL);
    new = ft_lstnew(content);
    ft_lstadd_back(&g_env, new);
    return (0);
}
