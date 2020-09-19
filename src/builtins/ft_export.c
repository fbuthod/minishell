/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 00:40:00 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 01:41:57 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list  *duplicate_list()
{
    t_list *tmp;
    t_list *new;
    t_list *head;
    t_env_var *content;
    t_env_var *tmp_c;

    tmp = g_env;
    head = NULL;
    while (tmp)
    {
        tmp_c = (t_env_var *)tmp->content;
        content = new_pair(tmp_c->key ? tmp_c->key : NULL,
                           tmp_c->value ? tmp_c->value : NULL);
        new = ft_lstnew(content);
        ft_lstadd_back(&head, new);
        tmp = tmp->next;
    }
    return (head);
}

void    swap(t_list *n1, t_list *n2)
{
    void *tmp;

    tmp = n1->content;
    n1->content = n2->content;
    n2->content = tmp;
}

t_boolean cmp_node(t_list *n1, t_list *n2)
{
    t_env_var *e1;
    t_env_var *e2;

    e1 = (t_env_var *)n1->content;
    e2 = (t_env_var *)n2->content;
    if (e1->key && e2->key && ft_strncmp(e1->key, e2->key, ft_strlen(e1->key) + 1) > 0)
        return (TRUE);
    return (FALSE);
}

void    sort_linked_list(t_list *head)
{
    t_boolean cont;
    t_list *copy;
    t_list *tmp;

    copy = head;
    cont = TRUE;
    while (cont)
    {
        cont = FALSE;
        tmp = head;
        while (tmp->next)
        {
            if (cmp_node(tmp, tmp->next))
            {
                swap(tmp, tmp->next);
                cont = TRUE;
            }
            tmp = tmp->next;
        }
    }
}

void    show()
{
    t_list *tmp_list_head;
    t_list *tmp_list;
    t_list *tmp_node;
    t_env_var *tmp_content;

    tmp_list_head = duplicate_list();
    tmp_list = tmp_list_head;
    sort_linked_list(tmp_list);
    while (tmp_list)
    {
        tmp_content = (t_env_var *)tmp_list->content;
        if (tmp_content->value)
            ft_printf("declare -X %s=\"%s\"\n", tmp_content->key, tmp_content->value);
        else if (tmp_content->key)
            ft_printf("declare -X %s\n", tmp_content->key);
        tmp_list = tmp_list->next;
    }
    while (tmp_list_head)
    {
        tmp_node = tmp_list_head->next;
        tmp_content = (t_env_var *)tmp_list_head->content;
        if (tmp_content && tmp_content->key)
            free(tmp_content->key);
        if (tmp_content && tmp_content->value)
            free(tmp_content->value);
        if (tmp_content)
            free(tmp_content);
        if (tmp_list_head)
            free(tmp_list_head);
        tmp_list_head = tmp_node;
    }
}

void    ft_export(t_command *cmd, t_boolean b)
{
    int i;
    char *tmp_key;
    char *tmp_value;

    g_last_state = 0;
    if (cmd->args[1] == NULL && b)
        show();
    else
    {
        i = 0;
        while (cmd->args[++i])
            if (cmd->args[i][0] == '=')
            {    
                if (b)
                    ft_printf("minishell: export: \"%s\" : identifiant non valable\n", cmd->args[i]);
            }
            else if (ft_strchr_chr(cmd->args[i], '='))
            {
                if (!(tmp_key = ft_calloc(ft_strchr_chr(cmd->args[i], '=') - cmd->args[i] + 1, 1)))
                {
                    g_last_state = 1;
                    return ;
                }
                ft_memcpy(tmp_key, cmd->args[i], ft_strchr_chr(cmd->args[i], '=') - cmd->args[i]);
                tmp_value = ft_strdup(ft_strchr_chr(cmd->args[i], '=') + 1);
                tmp_value = ft_remove_quotes(tmp_value);
                set_env_value(tmp_key, tmp_value);
                free(tmp_value);
                free(tmp_key);
            }
            else
                set_env_value(cmd->args[i], NULL);
    }
}
