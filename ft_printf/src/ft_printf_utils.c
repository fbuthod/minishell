/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:31:35 by ksam              #+#    #+#             */
/*   Updated: 2020/03/03 19:27:23 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

char	*ft_identifier(const char *str)
{
	char	*ptr_percent;

	ptr_percent = NULL;
	if ((ptr_percent = ft_strchr(str, '%')))
		return (++ptr_percent);
	return (ptr_percent);
}

int		ft_printf_with_arg(va_list *ap, t_printf *bag, const char *s)
{
	int	ret;

	ret = 0;
	if (s[bag->index] == '%')
	{
		ft_struct_reinitialize(bag);
		bag->index++;
		if (!(ret = ft_convert(ap, bag)))
			return (-1);
	}
	else
	{
		write(1, s + bag->index, 1);
		bag->count++;
		bag->index++;
	}
	return (1);
}
