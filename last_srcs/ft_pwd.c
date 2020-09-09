/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaud <gbaud@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 22:59:01 by gbaud             #+#    #+#             */
/*   Updated: 2020/09/08 23:02:10 by gbaud            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_cwd(void)
{
	char	buff[256];
	char	*path;

	if (getcwd(buff, 256) == NULL)
		return (NULL);
	path = ft_strdup(buff);
	return (path);
}

int		ft_pwd(t_cmd *cmd, t_builtin *builtin)
{
	char	*path;

	(void)builtin;
	path = ft_strdup(cmd->pwd);
	ft_printf("%s\n", path);
	free(path);
	return (0);
}

char	*ft_init_pwd(void)
{
	char	*path;

	if ((path = ft_get_cwd()) == NULL)
		return (ft_strdup("/"));
	return (path);
}
