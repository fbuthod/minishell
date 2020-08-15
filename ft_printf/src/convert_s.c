/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:14:53 by ksam              #+#    #+#             */
/*   Updated: 2020/02/19 15:23:44 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

void	ft_convert_s(t_printf *bag, va_list *ap)
{
	char	*specifier_s;

	specifier_s = va_arg(*ap, char *);
	ft_bag_initialize_s(bag);
	if (!specifier_s)
		specifier_s = "(null)";
	if ((size_t)bag->accuracy < ft_strlen(specifier_s))
	{
		if ((bag->width > 0) && (bag->flag_m == 0))
			ft_apply_width(bag, bag->accuracy);
		write(1, specifier_s, bag->accuracy);
		if ((bag->width > 0) && (bag->flag_m > 0))
			ft_apply_width(bag, bag->accuracy);
		bag->count += bag->accuracy;
	}
	else
	{
		if ((bag->width > 0) && (bag->flag_m == 0))
			ft_apply_width(bag, ft_strlen(specifier_s));
		write(1, specifier_s, ft_strlen(specifier_s));
		if ((bag->width > 0) && (bag->flag_m > 0))
			ft_apply_width(bag, ft_strlen(specifier_s));
		bag->count += ft_strlen(specifier_s);
	}
}

void	ft_bag_initialize_s(t_printf *bag)
{
	bag->index++;
	bag->flag_z = 0;
	bag->flag_s = 1;
}
