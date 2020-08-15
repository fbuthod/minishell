/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:16:51 by ksam              #+#    #+#             */
/*   Updated: 2020/02/19 15:29:04 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

int		ft_width(va_list *ap, t_printf *bag)
{
	int	ret;

	ret = 0;
	while (bag->spec[0] == '-')
	{
		ft_increase_index_spec(bag, 1);
		bag->flag_m = 1;
	}
	if ((bag->spec[0] == '0') && ((ret = ft_isdigit(bag->spec[1])) ||
		bag->spec[1] == '*'))
	{
		ft_increase_index_spec(bag, 1);
		bag->flag_z = 1;
	}
	if (bag->spec[0] == '0' && bag->spec[1] == '-')
	{
		ft_increase_index_spec(bag, 2);
		bag->flag_m = 1;
	}
	if (!(ret = ft_calcul(bag, ap)))
		return (-1);
	bag->width = bag->tmp;
	ft_format_width_as_negative(bag);
	return (1);
}

void	ft_increase_index_spec(t_printf *bag, int nb)
{
	bag->spec += nb;
	bag->index += nb;
}
