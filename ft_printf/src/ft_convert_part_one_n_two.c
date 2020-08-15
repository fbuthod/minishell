/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_part_one_n_two.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:16:05 by ksam              #+#    #+#             */
/*   Updated: 2020/02/24 16:45:22 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

int		ft_convert_part_one(va_list *ap, t_printf *bag)
{
	int	ret;

	ret = 0;
	if (*bag->spec == 'c')
		ft_convert_c(bag, ap);
	else if (*bag->spec == 's')
	{
		if (bag->accuracy != 0)
			ft_convert_s(bag, ap);
		else
		{
			if (bag->width > 0)
				ft_apply_width(bag, 0);
			va_arg(*ap, char *);
			bag->index++;
		}
	}
	else if (*bag->spec == 'p')
	{
		if (!(ret = ft_convert_p(bag, ap)))
			return (-1);
	}
	else if (*bag->spec == '%')
		ft_convert_percent(bag);
	return (1);
}

int		ft_convert_part_two(va_list *ap, t_printf *bag)
{
	int	ret;

	ret = 0;
	if ((*bag->spec == 'd') || (*bag->spec == 'i'))
	{
		if (!(ret = ft_convert_di(bag, ap)))
			return (-1);
	}
	else if (*bag->spec == 'u')
	{
		if (!(ret = ft_convert_u(bag, ap)))
			return (-1);
	}
	else if (*bag->spec == 'x' || *bag->spec == 'X')
	{
		if (!(ret = ft_convert_xx(bag, ap)))
			return (-1);
	}
	return (1);
}
