/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:15:41 by ksam              #+#    #+#             */
/*   Updated: 2020/02/19 14:41:15 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

int		ft_convert_u(t_printf *bag, va_list *ap)
{
	unsigned int	specifier_u;
	char			*base;
	char			*buffer;

	specifier_u = va_arg(*ap, unsigned int);
	bag->index++;
	if (bag->flag_z == 1 && (bag->accuracy > -1))
		bag->flag_z = 0;
	if (bag->accuracy > -1)
		ft_apply_precision(bag, specifier_u);
	base = ft_base(BASE10);
	if (!(buffer = ft_itoa_base(specifier_u, base)))
		return (-1);
	if (buffer[0] == '-')
		buffer++;
	if (specifier_u == 0 && bag->accuracy == 0)
		no_prec_no_specifier_(bag, buffer);
	else
	{
		if ((bag->width > 0) && (bag->flag_m == 0))
			ft_apply_width(bag, ft_strlen(buffer));
		write(1, buffer, ft_strlen(buffer));
	}
	ft_update_count_and_more(bag, buffer);
	return (1);
}
