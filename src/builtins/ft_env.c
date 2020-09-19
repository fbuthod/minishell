/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:50:00 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 01:17:32 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_var(void *content)
{
    t_env_var *env_var;

    env_var = (t_env_var *)content;
    if (env_var->key && env_var->value != NULL)
        ft_printf("%s=%s\n", env_var->key, env_var->value);
}

void    ft_env()
{
    ft_lstiter(g_env, print_var);
    g_last_state = 0;
}
