/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands_manager.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 07:09:18 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/17 03:57:30 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
