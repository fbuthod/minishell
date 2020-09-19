/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_part_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 11:24:35 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/19 11:27:04 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			trim_quotes(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		if ((args[i][0] == '\"' && args[i][ft_strlen(args[i]) - 1] == '\"') ||
			(args[i][0] == '\'' && args[i][ft_strlen(args[i]) - 1] == '\''))
			args[i] = ft_remove_quotes(args[i]);
		args[i] = apply_escape(args[i]);
		i++;
	}
}

int				fill_args(t_command *cmd_s, char *cmd)
{
	char **args;

	if (!(args = ft_split_quotes(cmd, is_spaceredirection)))
		return (FALSE);
	trim_tab(args);
	args = ft_remove_void_elem(args);
	if (!check_valid_command(args))
	{
		ft_printf("Parsing error\n");
		return (FALSE);
	}
	trim_quotes(args);
	cmd_s->args = args;
	return (TRUE);
}

char			**fd_parser(char **a)
{
	int		i;
	int		j;
	char	**res;

	i = -1;
	j = 0;
	while (a[++i])
		if (is_str(a[i], ">") || is_str(a[i], ">>") || is_str(a[i], "<"))
			j += 2;
	if (!(res = ft_calloc(i - j + 1, sizeof(char *))))
		return (NULL);
	j = -1;
	i = -1;
	while (a[++j])
		if (is_str(a[j], ">") || is_str(a[j], ">>"))
		{
			setup_output(a[j], a[1 + j]);
			j++;
		}
		else if (is_str(a[j], "<"))
			setup_input(a[++j]);
		else
			res[++i] = ft_strdup(a[j]);
	ft_free_strs_tab(a);
	return (res);
}

t_command		*make_command(char *cmd)
{
	t_command	*command;
	int			i;

	if (!(command = malloc(sizeof(t_command))))
		return (NULL);
	if ((i = fill_command(command, cmd)) < 0)
		return (ft_free_return(command) ? NULL : NULL);
	if (!(fill_args(command, cmd)))
	{
		free(command->cmd);
		free(command);
		return (NULL);
	}
	command->args = fd_parser(command->args);
	return (command);
}

char			*ft_isinpath(char *executable)
{
	struct stat	buf;
	char		**tmp_path;
	char		*complete_path;
	int			i;

	i = 0;
	if (stat(executable, &buf) >= 0)
		return (ft_strdup(executable));
	if (get_env_value("PATH"))
	{
		tmp_path = ft_split(get_env_value("PATH")->value, ':');
		while (tmp_path[i])
		{
			complete_path = ft_strjoin(tmp_path[i], "/");
			complete_path = ft_strfjoin(complete_path, executable, 1);
			if (stat(complete_path, &buf) >= 0 && free_tab_str(tmp_path))
				return (complete_path);
			free(complete_path);
			i++;
		}
		free_tab_str(tmp_path);
	}
	return (NULL);
}
