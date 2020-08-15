/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:09:20 by ksam              #+#    #+#             */
/*   Updated: 2020/02/15 11:09:21 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	if (dst == 0 || src == 0)
		return (0);
	while ((src[i] != '\0') && size && (i < (size - 1)))
	{
		dst[i] = src[i];
		i++;
	}
	if (size)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
