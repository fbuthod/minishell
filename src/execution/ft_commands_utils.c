/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 07:09:18 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/11 07:13:31 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command    *get_content(t_list *node)
{
    t_command *cmd;

    cmd = (t_command *)node->content;
    return cmd;
}

char        *get_next(t_list *node)
{
    return (get_content(node)->next);
}