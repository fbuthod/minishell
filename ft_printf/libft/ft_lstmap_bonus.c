/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:04:57 by ksam              #+#    #+#             */
/*   Updated: 2020/02/15 11:04:59 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f) (void *), void (del) (void *))
{
	t_list	*newlist;
	t_list	*first;

	if (f != NULL && lst != NULL && del != NULL)
	{
		first = NULL;
		while (lst != NULL)
		{
			newlist = ft_lstnew((*f)(lst->content));
			if (newlist == NULL)
			{
				ft_lstclear(&first, del);
				return (NULL);
			}
			ft_lstadd_back(&first, newlist);
			lst = lst->next;
		}
		return (first);
	}
	return (NULL);
}
