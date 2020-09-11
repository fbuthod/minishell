/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 23:25:48 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/10 06:53:31 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char* replace_word(char* s, int start, char* o, char* n) 
{ 
    char *res;

    res = ft_strfjoin(ft_substr(s, 0, start), n, 1);
    res = ft_strfjoin(res, &s[start + ft_strlen(o)], 1);
    free(s);
    return (res);
}

char    *replace_env_var(char *cmd)
{
    t_split_quotes	states;
    char *res;
    char *key;
    char *value;
    int i;
    int j;

    i = 0;
	states.d_quote = 0;
	states.s_quote = 0;
	states.escaped = 0;
    res = ft_strdup(cmd);
    while (res[i])
    {
		check_quotes(&states, res, i);
        if (!states.s_quote && res[i] == '$')
        {
            j = i;
            if (res[i + 1] != '?')
            {
                while (ft_isalnum(res[++j]) || res[j] == '_')
                    ;
                key = ft_substr(res, i, j - i);
                value = get_env_value(&key[1])->value;
            }
            else if ((key = ft_strdup("$?")))
                value = ft_itoa(g_last_state);
            if (value != NULL)
                res = replace_word(res, i, key, value);
            i += (value) ? ft_strlen(value) - 1 : ft_strlen(key) - 1;
            if (ft_strncmp(key, "$?", 3) == 0 && ft_free_return(key))
                free(value);
        }
        states.escaped = (res[i] == '\\') ? states.escaped + 1 : 0;
        i++;
    }
    free(cmd);
    return (res);
}

