/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:53:38 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/05 10:22:53 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *check_path(char *path, char *exectutable)
{
    struct stat buf;
    char *line_inter;
    char *line;

    line_inter = ft_strjoin(path, "/");
    line = ft_strjoin(line_inter, exectutable);
    free(line_inter);
    if (stat(line, &buf) >= 0)
        return (line);
    free(line);
    return (NULL);
}

char    *ft_isinpath(char *executable)
{
    int i;
    char **strs;
    char *res;

    i = 0;
    while (g_env[i] && ft_strncmp(g_env[i], "PATH=", 5))
        i++;
    strs = ft_split(&g_env[i][5], ':');
    i = -1;
    while (strs[++i])
        if ((res = check_path(strs[i], executable)) != NULL)
        {
            free_tab_str(strs);
            return (res);
        }
    free_tab_str(strs);
    return (NULL);
}

int     start_process(char *path, char **args)
{
    pid_t   pid;
    int     status;
    
    pid = fork();
    if (pid < 0)
        ft_printf("Fork error %s\n", path);
    else if (pid == 0)
    {
        if (execve(path, args, g_env) == -1)
        {
            ft_printf("Execution error %s\n", path);
            return (1);
        }
        exit(0);
    }
    else
        wait(&status);
    return (0);
}