/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_filler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 06:51:19 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/08 08:06:31 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_remove_void(char **arr)
{
    int i;
    int count;
    char **res;

    i = 0;
    count = 0;
    trim_tab(arr);
    while (arr[i])
        if (ft_strncmp(arr[i++], "", 1))
            count++;
    if (!(res = malloc(sizeof(char *) * (count + 1))))
        return (NULL);    
    res[count] = NULL;
    i = -1;
    count = 0;
    while (arr[++i])
        if (ft_strncmp(arr[i], "", 1))
            res[count++] = ft_strdup(arr[i]);
    free_tab_str(arr);
    return (res);
}

char **command_from_string(char *cmd_param)
{
    char **res;

    res = ft_split_quotes(cmd_param, is_space);
    res = ft_remove_void(res);
    return (res);
}

/*

ls   -l -a ../


ls | ls -la > test | grep .


tmp = 0;
foreach :
    if (elem[i + 1] == '|')
        exec
    else if (elem[i + 1] == '>' || elem[i + 1] == '>>')
        tmp = i;
        while (elem[i + 1] == '>' || elem[i + 1] == '>>')
            update_fd()
        exec elem[tmp];
    else if (elem[i + 1] == '<')
        update_in();
    i+=2;
reset_fd();
*/