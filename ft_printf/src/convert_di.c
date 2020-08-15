/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:14:26 by ksam              #+#    #+#             */
/*   Updated: 2020/02/20 13:06:03 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

int		ft_convert_di(t_printf *bag, va_list *ap)
{
	int		specifier_di;
	char	*buffer;

	specifier_di = va_arg(*ap, int);
	bag->index++;
	if_prec_zero(bag);
	specifier_di = neg_creat(bag, specifier_di);
	if (bag->accuracy > -1 && !(bag->flag_z = 0))
		ft_apply_precision(bag, specifier_di);
	if (!(buffer = ft_itoa(specifier_di)))
		return (-1);
	if (bag->accuracy == 0 && specifier_di == 0)
		no_prec_no_specifier_(bag, buffer);
	width_without_minus(buffer, specifier_di, bag);
	if (specifier_di == -2147483648)
		if_di_is_int_min(buffer, bag);
	else
	{
		neg_apply(bag);
		write(1, buffer, ft_strlen(buffer));
	}
	ft_update_count_and_more(bag, buffer);
	return (1);
}

void	width_without_minus(char *buffer, int specifier_di, t_printf *bag)
{
	if ((bag->width > 0) && (bag->flag_m == 0))
	{
		if (specifier_di < 0 && bag->flag_z != 0 && bag->width > 11)
			bag->min = 1;
		ft_apply_width(bag, ft_strlen(buffer));
	}
}

void	if_di_is_int_min(char *buffer, t_printf *bag)
{
	if (buffer[0] == '-' && (bag->accuracy == -2 || bag->min == 1))
		buffer[0] = '0';
	write(1, buffer, ft_strlen(buffer));
}

int		neg_creat(t_printf *bag, int specifier)
{
	if (specifier < 0 && specifier != -2147483648)
	{
		specifier *= -1;
		bag->neg = 1;
	}
	return (specifier);
}

void	neg_apply(t_printf *bag)
{
	if (bag->neg > 0)
	{
		write(1, "-", 1);
		bag->count++;
		bag->neg = 0;
		if (bag->width && bag->flag_m != 0)
			bag->width--;
	}
}
