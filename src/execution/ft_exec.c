/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 02:52:52 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/11 07:39:55 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec_process(t_command *cmd)
{
    execvp(cmd->cmd, cmd->args);
}

void    loop_pipe(t_list **head) 
{
    int   p[2];
    pid_t pid;
    int   fd_in = 0;

    while (*head != NULL)
    {
        pipe(p);
        if ((pid = fork()) == -1)
        {
          exit(1);
        }
        else if (pid == 0)
        {
            dup2(fd_in, 0); //change the input according to the old one 
            if ((*head)->next != NULL)
                dup2(p[1], 1);
            close(p[0]);
            exec_process(get_content(*head));
            exit(1);
        }
        else
        {
            wait(NULL);
            close(p[1]);
            fd_in = p[0];
            *head = (*head)->next;
        }
    }
}

void    exec_list(t_list *head)
{
    t_command *tmp;

    tmp = (t_command *)((head)->content);
    while (head)
    {
        if (tmp->next && !ft_strncmp(tmp->next, "|", 2))
            loop_pipe(&head);
        else
            head = head->next;
        if (head)
            tmp = (t_command *)((head)->content);
    }
}
