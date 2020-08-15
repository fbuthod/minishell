/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:08:51 by ksam              #+#    #+#             */
/*   Updated: 2020/03/05 20:07:10 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len;

	i = -1;
	j = ft_strlen((char*)s1);
	len = j + ft_strlen((char*)s2);
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
