/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:14:15 by ksam              #+#    #+#             */
/*   Updated: 2020/02/15 14:38:46 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

void	ft_convert_c(t_printf *bag, va_list *ap)
{
	char	specifier_c;

	specifier_c = va_arg(*ap, int);
	bag->index++;
	ft_print_char(bag, specifier_c);
}
