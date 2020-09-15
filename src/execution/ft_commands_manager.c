/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 07:09:18 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/14 02:27:05 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command   *get_current(t_list *head)
{
    return ((t_command *)(head->content));
}

t_command   *get_left(t_list *head)
{
    if (!head->prev)
        return (NULL);
    return ((t_command *)(head->prev->content));
}

t_command   *get_right(t_list *head)
{
    if (!head->next)
        return (NULL);
    return ((t_command *)(head->next->content));
}

t_boolean   is_str(char *str, char *red)
{
    if (!str && !red)
        return (TRUE);
    else if (!str || !red)
        return (FALSE);
    if (ft_strncmp(str, red, ft_strlen(red) + 1))
        return (FALSE);
    return (TRUE);
}