/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:05:19 by ksam              #+#    #+#             */
/*   Updated: 2020/02/15 11:05:21 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *a;

	a = (t_list *)malloc(sizeof(t_list) * 1);
	if (a == 0)
		return (a);
	a->content = content;
	a->next = NULL;
	return (a);
}
