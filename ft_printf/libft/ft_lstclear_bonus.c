/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:04:04 by ksam              #+#    #+#             */
/*   Updated: 2020/02/15 11:04:06 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	while (lst && *lst)
	{
		del((*lst)->content);
		free(*lst);
		(*lst)->content = NULL;
		*lst = (*lst)->next;
	}
}
