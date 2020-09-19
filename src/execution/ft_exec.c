/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 02:52:52 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 11:27:19 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			exec_system(t_command *cmd)
{
	char *path;
	char **tmp_env;

	if ((path = ft_isinpath(cmd->cmd)))
	{
		tmp_env = env_to_tab();
		if (execve(path, cmd->args, tmp_env) == -1)
		{
			free(path);
			ft_free_strs_tab(tmp_env);
			ft_printf("Execution error %s\n", path);
			g_last_state = 127;
			return ;
		}
		g_last_state = 0;
		free(path);
		ft_free_strs_tab(tmp_env);
	}
	else
	{
		g_last_state = 127;
		ft_printf("%s : commande introuvale\n", cmd->cmd);
	}
}

void			exec_process(char *cmd)
{
	t_command *cmd_struct;

	if (!(cmd_struct = make_command(cmd)))
		return ;
	if (!ft_strncmp(cmd_struct->cmd, "echo", 5))
		ft_echo(cmd_struct);
	else if (!ft_strncmp(cmd_struct->cmd, "cd", 3))
		;
	else if (!ft_strncmp(cmd_struct->cmd, "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd_struct->cmd, "export", 7))
		ft_export(cmd_struct, TRUE);
	else if (!ft_strncmp(cmd_struct->cmd, "unset", 6))
		ft_unset(cmd_struct);
	else if (!ft_strncmp(cmd_struct->cmd, "env", 4))
		ft_env();
	else if (!ft_strncmp(cmd_struct->cmd, "exit", 5))
		ft_exit(cmd_struct);
	else
		exec_system(cmd_struct);
	ft_free_strs_tab(cmd_struct->args);
	free(cmd_struct->cmd);
	free(cmd_struct);
}

void			forked(int *fd_in, int (*p)[2], char **cmd_list)
{
	dup2(*fd_in, 0);
	if (*(cmd_list + 1) != NULL)
		dup2((*p)[1], 1);
	close((*p)[0]);
	exec_process((*cmd_list));
	if (g_in > 0)
		close(g_in);
	if (g_out > 0)
		close(g_out);
	exit(g_last_state);
}

void			main_process(int pid, char *cmd_list)
{
	t_command	*cmd_struct;
	int			status;

	waitpid(pid, &status, 0);
	if (!ft_strncmp(cmd_list, "cd ", 3) ||
		!ft_strncmp(cmd_list, "export ", 7) ||
		!ft_strncmp(cmd_list, "unset ", 6))
	{
		cmd_struct = make_command(cmd_list);
		if (!ft_strncmp(cmd_struct->cmd, "cd", 3))
			ft_cd(cmd_struct);
		else if (!ft_strncmp(cmd_struct->cmd, "export", 6))
			ft_export(cmd_struct, FALSE);
		else if (!ft_strncmp(cmd_struct->cmd, "unset", 5))
			ft_unset(cmd_struct);
		ft_free_strs_tab(cmd_struct->args);
		free(cmd_struct->cmd);
		free(cmd_struct);
	}
	else
		g_last_state = WEXITSTATUS(status);
}

int				exec_command_list(char **cmd_list)
{
	pid_t		pid;
	int			p[2];
	int			fd_in;

	fd_in = 0;
	while (*cmd_list != NULL)
	{
		if (!is_str(*cmd_list, "|") && pipe(p) != -1)
		{
			if ((pid = fork()) == -1)
				exit(1);
			else if (pid == 0)
				forked(&fd_in, &p, cmd_list);
			else
			{
				main_process(pid, *cmd_list);
				if (check_exit(*cmd_list))
					return (1);
				close(p[1]);
				fd_in = p[0];
			}
		}
		cmd_list++;
	}
	return (0);
}
