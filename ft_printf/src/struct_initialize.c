/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_initialize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:16:36 by ksam              #+#    #+#             */
/*   Updated: 2020/02/20 12:01:59 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

void	ft_struct_initialize(t_printf *list)
{
	list->index = 0;
	list->count = 0;
	list->len_specifier = 0;
	list->accuracy = -1;
	list->width = -1;
	list->spec = NULL;
	list->tmp = 0;
	list->neg = 0;
	list->min = 0;
	list->flag_z = 0;
	list->flag_m = 0;
	list->flag_s = 0;
}

void	reset_flag(t_printf *bag)
{
	if (bag->flag_z != 0)
		bag->flag_z = 0;
	if (bag->flag_m != 0)
		bag->flag_m = 0;
	if (bag->flag_s != 0)
		bag->flag_s = 0;
}

void	ft_struct_reinitialize(t_printf *bag)
{
	bag->len_specifier = 0;
	bag->accuracy = -1;
	bag->width = -1;
	bag->tmp = 0;
	bag->neg = 0;
	bag->min = 0;
}
