/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:51:46 by ksam              #+#    #+#             */
/*   Updated: 2020/02/19 16:02:02 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

void	ft_apply_width(t_printf *bag, int len)
{
	if ((len + bag->neg) < bag->width)
	{
		if (bag->flag_m > 0 && bag->accuracy > len && bag->flag_s == 0)
			bag->width -= bag->accuracy;
		else
			bag->width = bag->width - (len + bag->neg);
		ft_write_width(bag);
	}
	reset_flag(bag);
	bag->width = -1;
}

void	ft_write_width(t_printf *bag)
{
	if (bag->width > 0)
	{
		bag->count += bag->width;
		if (bag->min == 1)
		{
			bag->width--;
			write(1, "-", 1);
		}
		while (bag->width-- > 0)
		{
			if (bag->flag_z > 0)
			{
				neg_apply(bag);
				write(1, "0", 1);
			}
			else
				write(1, " ", 1);
		}
	}
}

void	ft_format_width_as_negative(t_printf *bag)
{
	if (bag->width < 0)
	{
		bag->width *= -1;
		bag->flag_m = 1;
	}
	if (bag->flag_m > 0 && bag->flag_z > 0)
		bag->flag_z = 0;
}
