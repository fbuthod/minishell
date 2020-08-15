/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:09:49 by ksam              #+#    #+#             */
/*   Updated: 2020/02/15 11:09:56 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	unsigned	i;
	char		*dst;

	if (!(s == NULL || f == NULL))
	{
		i = ft_strlen((char *)s);
		dst = malloc(sizeof(*s) * ((i + 1)));
		if (dst == NULL)
			return (dst);
		i = 0;
		while (s[i] != '\0')
		{
			dst[i] = f(i, s[i]);
			i++;
		}
		dst[i] = '\0';
		return (dst);
	}
	return (0);
}
