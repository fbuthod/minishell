/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:13:58 by ksam              #+#    #+#             */
/*   Updated: 2020/02/19 13:21:57 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

int		ft_convert(va_list *ap, t_printf *bag)
{
	int		ret;
	char	*ptr;

	ptr = NULL;
	ret = 0;
	while ((ret = ft_isdigit(bag->spec[0])) || bag->spec[0] == '*' ||
		bag->spec[0] == '-')
	{
		ret = 0;
		if (!(ret = ft_width(ap, bag)))
			return (-1);
	}
	if (bag->spec[0] == '.')
	{
		if (!(ret = ft_precision(ap, bag)))
			return (-1);
	}
	if ((ret = ft_isalpha(bag->spec[0])) || bag->spec[0] == '%')
	{
		if (!(ret = select_specifier(ap, bag, ptr)))
			return (-1);
	}
	return (bag->count);
}
