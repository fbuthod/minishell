/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 02:52:52 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/15 06:46:45 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    simple_exec(t_command *cmd)
{
    ft_printf("EXEC [%s]\n", cmd->cmd);
}

int         fill_command(t_command *cmd_s, char *cmd)
{
    int i;

    i = 0;
    while (cmd[i] && cmd[i] != ' ')
        i++;
    if (!(cmd_s->cmd = ft_calloc(i + 1, 1)))
        return (-1);
    ft_memcpy(cmd_s->cmd, cmd, i);
    return (i);
}

char        **ft_remove_void_elem(char **args)
{
    char **res;
    int count;
    int i;
    int j;

    i = -1;
    count = 0;
    while (args[++i])
        if (!is_str(args[i], ""))
            count++;
    if (!(res = ft_calloc(count + 1, sizeof(char *))))
    {
        free_tab_str(args);
        return (NULL);
    }
    i = -1;
    j = 0;
    while (args[++i])
        if (!is_str(args[i], ""))
        {
            res[j] = ft_strdup(args[i]);
            j++;
        }
    return (res);
}

int         fill_args(t_command *cmd_s, char *cmd, int i)
{
    char **args;

    if (!(args = ft_split_quotes(&cmd[i], is_spaceredirection)))
        return (FALSE);
    args = trim_tab(args);
    args = ft_remove_void_elem(args);

    cmd_s->args = args;
    return (TRUE);
}

char        **fd_parser(char **args)
{
    int i;
    int j;
    int count;
    char **res;

    i = -1;
    count = 0;
    while (args[++i])
        if (is_str(args[i], ">") || is_str(args[i], ">>") || is_str(args[i], "<"))    
            count += 2;
    i -= count;
    if (!(res = ft_calloc(i + 1, sizeof(char *))))
        return (NULL);
    j = -1;
    i = -1;
    while (args[++j])
        if (is_str(args[j], ">") || is_str(args[j], ">>"))
        {
            setup_output(args[j], args[j + 1]);
            j++;
        }
        else if (is_str(args[j], "<"))
        {
            setup_input(args[j]);
            j++;
            ft_printf("SET INPUT %s\n", args[j]);
        }
        else
            res[++i] = ft_strdup(args[j]);
    ft_free_strs_tab(args);
    return (res);
}

// TODO: Bug si une seul <
// TODO: Check non double redirection
t_command   *make_command(char *cmd)
{
    t_command   *command;
    int         i;

    if (!(command = malloc(sizeof(t_command))))
        return (NULL);
    if ((i = fill_command(command, cmd)) < 0)
        return (ft_free_return(command) ? NULL : NULL);
    if (!(fill_args(command, cmd, 0)))
    {
        free(command->cmd);
        free(command);
        return (NULL);
    }
    command->args = fd_parser(command->args);
    return (command);
}

void    exec_process(char *cmd)
{
    t_command *cmd_struct;

    if (!(cmd_struct = make_command(cmd)))
        return ;
    execvp(cmd_struct->cmd, cmd_struct->args);
}

void    exec_command_list(char **cmd_list)
{
    int   p[2];
    pid_t pid;
    int   fd_in = 0;

    while (*cmd_list != NULL)
    {
        if (!is_str(*cmd_list, "|"))
        {
            pipe(p);
            if ((pid = fork()) == -1)
                exit(1);
            else if (pid == 0)
            {
                dup2(fd_in, 0); //change the input according to the old one 
                if (*(cmd_list + 1) != NULL)
                    dup2(p[1], 1);
                close(p[0]);
                exec_process((*cmd_list));
                exit(1);
            }
            else
            {
                wait(NULL);
                close(p[1]);
                fd_in = p[0]; //save the input for the next command
            }
        }
        cmd_list++;
    }
}
