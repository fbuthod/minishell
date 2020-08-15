/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbuthod- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 04:45:44 by fbuthod-          #+#    #+#             */
/*   Updated: 2020/03/13 20:07:29 by fbuthod-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		gnl_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void		*gnl_memset(void *b, int c, size_t len)
{
	unsigned char	*s;

	s = b;
	while (len-- > 0)
		*s++ = c;
	return (b);
}

char		*gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len;

	i = -1;
	j = gnl_strlen((char*)s1);
	len = j + gnl_strlen((char*)s2);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (++i < j)
		str[i] = s1[i];
	j = 0;
	while (i < len)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

void		*gnl_calloc(size_t count, size_t size)
{
	size_t	*p;
	size_t	a;

	a = (count * size);
	p = malloc(a);
	if (p == 0)
		return (p);
	gnl_memset(p, 0, a);
	return ((void *)p);
}

char		*gnl_substr(char *s, unsigned int start, size_t len)
{
	size_t	count;
	size_t	size;
	char	*tab;

	count = 0;
	if (!s)
		return (NULL);
	if (gnl_strlen(s) < start)
		return (gnl_calloc(1, 1));
	size = gnl_strlen(s + start);
	if (size < len)
		len = size;
	if (!(tab = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (count < len)
	{
		tab[count] = s[start + count];
		count++;
	}
	tab[count] = '\0';
	return (tab);
}
