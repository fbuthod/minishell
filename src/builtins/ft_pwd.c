/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 01:02:33 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/16 01:03:25 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pwd()
{
    char buff[FILENAME_MAX];

    getcwd(buff, FILENAME_MAX);
    ft_printf("%s\n", buff);
    g_last_state = 0;
}