/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:16:14 by ksam              #+#    #+#             */
/*   Updated: 2020/03/03 19:27:04 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

int		ft_printf(const char *string, ...)
{
	int			ret;
	t_printf	bag;
	va_list		ap;

	va_start(ap, string);
	ft_struct_initialize(&bag);
	ret = 0;
	if (!(bag.spec = ft_identifier(string)))
	{
		bag.count = write(1, string, ft_strlen(string));
		return (bag.count);
	}
	while (string[bag.index] != '\0' && (bag.index <= ft_strlen(string)))
	{
		if (!(ret = ft_printf_with_arg(&ap, &bag, string)))
			return (-1);
		bag.spec = ft_identifier(string + bag.index);
	}
	va_end(ap);
	return (bag.count);
}
