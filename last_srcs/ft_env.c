/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:15:22 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/08 23:17:01 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_suppr_var(int place)
{
    int i;
    int k;
    char **temp;

    i = 0;
    k = 0;
    while (g_env[i] != 0)
        i++;
    if (!(temp = malloc((i + 1) * sizeof(char*))))
        return (0);
    i = 0;
    while (g_env[k] != 0)
    {
        if (k == place)
            k++;
        else
        {
            temp[i] = ft_strdup(g_env[k]);
            i++;
            k++;
        }
    }
    temp[i] = 0;
    g_env = temp;
    return (0);
}

int ft_unset(char *cmd, int i)
{
    int j;
    int k;
    
    j = 0;
    k = 0;
    while (cmd[i] != 0 && cmd[i] != ' ' && cmd[i] != ';')
        i++;
    while (g_env[j] != 0)
    {
        while (g_env[j][k] == cmd[k] && k <= i)
            k++;
        if (k == i)
            return (ft_suppr_var(j));
        else
            j++;
    }
    return (i + 6);
}

void get_env(char *cmd)
{
	int index;
	int i;

	index = 0;
	while (g_env[index])
    {
        i = 0;
        while ((g_env[index][i] != 0) && (g_env[index][i] != '='))
            i++;
        if (ft_strncmp(g_env[index], cmd, i) == 0)
        {
            while (g_env[index][i+1] != 0)
            {
                ft_printf("%c", g_env[index][i+1]);
                i++;
            }
        }
        index++;
    }
}

int ft_replace_var(char *var, int place)
{
    int i;
    int k;
    char **temp;

    i = 0;
    k = 0;
    while (g_env[i] != 0)
        i++;
    if (!(temp = malloc((i + 1) * sizeof(char*))))
        return (0);
    i = 0;
    while (g_env[k] != 0)
    {
        if (k == place)
            k++;
        else
        {
            temp[i] = ft_strdup(g_env[k]);
            i++;
            k++;
        }
    }
    temp[i] = ft_strdup(var);
    temp[i+1] = 0;
    g_env = temp;
    return (1);
}

int ft_verif_existant(char *var)
{
    int i;
    int j;
    int k;
    
    i = 0;
    j = 0;
    k = 0;
    while (var[i] != 0 && var[i] != '=')
        i++;
    while (g_env[j] != 0)
    {
        while (g_env[j][k] == var[k] && k < i+1)
            k++;
        if (k == i + 1)
            return (ft_replace_var(var, j));
        else
            j++;
    }
    return (0);
}

int ft_verif_var(char *var)
{
    int i;
    int nb_egual;
    
    i = 0;
    nb_egual = 0;
    while (var[i] != 0)
    {
        if (var[i] == '=')
            nb_egual++;
        i++;
    }
    if (nb_egual == 1)
        return (ft_verif_existant(var));
    else
        return (1);
}

int set_env(char *cmd)
{
    int index;
    int i;
    int return_value;
    char **temp;
    char *var;

    i = 0;
    index = 0;
    temp = 0;
    while (cmd[i] != ' ' && cmd[i] != ';' && cmd[i] != 0)
        i++;
    if (!(var = malloc((i + 1) * sizeof(char))))
        return (0);
    return_value = i;
    while (index < i)
    {
        var[index] = cmd[index];
        index++;
    }
    var[index] = 0;
    i = 0;
    index = 0;
    i = ft_verif_var(var);
    if (i == 0)
    {
        while (g_env[index])
            index++;
        if (!(temp = malloc((index + 2) * sizeof(char*))))
            return (0);
        while (i < index)
        {
            temp[i] = ft_strdup(g_env[i]);
            i++;
        }
        temp[i] = ft_strdup(var);
        g_env = temp;
    }
    return (return_value);
}

int ft_env(char *cmd)
{
    int i;

    i = 0;
    get_env(&cmd[i]);
    while (cmd[i] != 0 && cmd[i] != ' ' && cmd[i] != ';')
        i++;
    while (cmd[i] == ' ')
		i++;
    return (i + 1);
}

int ft_export(char *cmd, int i)
{
    int index;

    index = 0;
    while (cmd[i] == ' ')
        i++;
    if (cmd[i] != ';' && cmd[i] != 0)
        i += set_env(&cmd[i]);
    else
    {
        while (g_env[index] != 0)
            ft_printf("%s\n", g_env[index++]);
    }
    return (i);
}