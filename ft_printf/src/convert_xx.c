/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_xx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:43:09 by ksam              #+#    #+#             */
/*   Updated: 2020/02/19 14:40:49 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

int		ft_convert_xx(t_printf *bag, va_list *ap)
{
	unsigned int	specifier_x;
	char			*base;
	char			*buffer;

	specifier_x = va_arg(*ap, unsigned int);
	bag->index++;
	if (bag->flag_z == 1 && (bag->accuracy > -1))
		bag->flag_z = 0;
	base = detect_specifier_x(bag);
	if (!(buffer = ft_itoa_base(specifier_x, base)))
		return (-1);
	if (bag->accuracy > -1)
		ft_is_accuracy(bag, buffer);
	if (bag->accuracy == 0 && specifier_x == 0)
		no_prec_no_specifier_(bag, buffer);
	if ((bag->width > 0) && (bag->flag_m == 0))
		ft_apply_width(bag, ft_strlen(buffer));
	write(1, buffer, ft_strlen(buffer));
	ft_update_count_and_more(bag, buffer);
	return (1);
}

void	ft_is_accuracy(t_printf *bag, char *buffer)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	str[ft_strlen(buffer)] = '\0';
	str = ft_memset(str, '4', ft_strlen(buffer));
	bag->tmp = ft_atoi(str);
	free(str);
	ft_apply_precision(bag, bag->tmp);
}

char	*detect_specifier_x(t_printf *bag)
{
	char	*base;

	if (bag->spec[0] == 'X')
		base = ft_base(BASE16MA);
	if (bag->spec[0] == 'x')
		base = ft_base(BASE16mi);
	return (base);
}

int		ft_count(long n)
{
	long i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}
