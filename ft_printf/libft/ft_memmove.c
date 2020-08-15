/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:06:35 by ksam              #+#    #+#             */
/*   Updated: 2020/02/15 11:06:37 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (dst == 0 && src == 0)
		return (0);
	if (s < d)
	{
		s += len;
		d += len;
		while (len-- > 0)
			*--d = *--s;
	}
	else
	{
		while (len-- > 0)
			*d++ = *s++;
	}
	return (dst);
}
