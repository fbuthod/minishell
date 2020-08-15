/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 04:58:32 by ksam              #+#    #+#             */
/*   Updated: 2020/03/09 18:47:55 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*newptr;

	if (!size && ptr)
	{
		if (!(newptr = malloc(1)))
			return (NULL);
		free(ptr);
		ptr = NULL;
		return (newptr);
	}
	if (!(newptr = malloc(size)))
		return (NULL);
	if (ptr)
	{
		ft_memcpy(newptr, ptr, size);
		free(ptr);
		ptr = NULL;
	}
	return (newptr);
}
