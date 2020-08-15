/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:14:45 by ksam              #+#    #+#             */
/*   Updated: 2020/02/19 13:18:13 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

void	ft_convert_percent(t_printf *bag)
{
	bag->flag_s = 1;
	bag->index++;
	ft_print_char(bag, '%');
}
