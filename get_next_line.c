/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbuthod- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 04:45:44 by fbuthod-          #+#    #+#             */
/*   Updated: 2020/03/13 20:07:29 by fbuthod-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(char **line)
{
	static t_line	list;

	if ((list.a_read = read(STDIN_FILENO, 0, 0) < 0) || line == NULL ||
			BUFFER_SIZE <= 0 ||
			!(list.buffer_read = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (!(list.b_index = 0) && !(list.buffer_stock))
	{
		if (!(list.buffer_stock = malloc(1)))
			return (-1);
		list.buffer_stock[0] = '\0';
	}
	list.a_read = 1;
	while (!(list.b_index = ft_strichr(list.buffer_stock, '\n')) &&
			(list.a_read = read(STDIN_FILENO, list.buffer_read, BUFFER_SIZE)) != 0)
	{
		list.buffer_read[list.a_read] = '\0';
		if (!(list.buffer_stock = gnl_strjoin(list.buffer_stock,
						list.buffer_read)))
			return (-1);
	}
	(list.b_index < 0) ? (list.b_index = 0) : 0;
	if (list.a_read == 0)
		return (end_condition(&list, line));
	return (buffer_update(&list, line));
}

int		buffer_update(t_line *list, char **line)
{
	if (!(*line = gnl_substr(list->buffer_stock, 0, list->b_index)) ||
			!(list->buffer_temp = gnl_substr(list->buffer_stock,
					list->b_index + 1, gnl_strlen(list->buffer_stock))))
		return (-1);
	free(list->buffer_read);
	free(list->buffer_stock);
	list->buffer_stock = list->buffer_temp;
	return (1);
}

int		end_condition(t_line *list, char **line)
{
	if (list->buffer_stock == NULL)
	{
		if (!(*line = gnl_calloc(1, 1)))
			return (-1);
	}
	else
	{
		if (!(*line = gnl_substr(list->buffer_stock, 0,
						gnl_strlen(list->buffer_stock))))
			return (-1);
	}
	free(list->buffer_stock);
	list->buffer_stock = NULL;
	free(list->buffer_read);
	return (0);
}

int		ft_strichr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if ((*(s + i) == (char)c) && i == 0)
		return (-42);
	while (*(s + i) != '\0')
	{
		if (*(s + i) == (char)c)
			return (i);
		i++;
	}
	return (0);
}