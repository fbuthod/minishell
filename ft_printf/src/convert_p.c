/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:14:35 by ksam              #+#    #+#             */
/*   Updated: 2020/02/19 16:25:04 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

int		ft_convert_p(t_printf *bag, va_list *ap)
{
	unsigned long	specifier_p;
	char			*base;
	char			*buffer;

	specifier_p = va_arg(*ap, unsigned long);
	bag->index++;
	base = ft_base(BASE16mi);
	if (!(buffer = ft_itoa_base(specifier_p, base)))
		return (-1);
	if (specifier_p == 0 && bag->accuracy == 0)
		buffer[0] = '\0';
	if ((bag->width > 0) && (bag->accuracy <= 1) && bag->flag_m == 0)
		ft_apply_width(bag, ft_strlen(buffer) + 2);
	write(1, "0x", 2);
	write(1, buffer, ft_strlen(buffer));
	if ((bag->width > 0) && (bag->flag_m > 0))
		ft_apply_width(bag, ft_strlen(buffer) + 2);
	bag->count += ft_strlen(buffer) + 2;
	free(buffer);
	return (1);
}
