/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:16:28 by ksam              #+#    #+#             */
/*   Updated: 2020/02/20 12:42:33 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

int		ft_precision(va_list *ap, t_printf *bag)
{
	int	ret;

	ret = 0;
	while (bag->spec[0] == '.')
		ft_increase_index_spec(bag, 1);
	if (!(ret = ft_calcul(bag, ap)))
		return (-1);
	bag->accuracy = bag->tmp;
	return (1);
}

void	ft_apply_precision(t_printf *bag, long long specifier)
{
	char	*tmp;

	tmp = ft_itoa(specifier);
	bag->len_specifier = ft_strlen(tmp);
	if (specifier < 0 && (bag->accuracy > 11))
		bag->neg = 1;
	if (bag->len_specifier < bag->accuracy)
	{
		if (bag->width > 0 && bag->flag_m == 0)
			ft_apply_width(bag, bag->accuracy);
		bag->len_specifier = (bag->accuracy - bag->len_specifier);
		bag->count += (bag->len_specifier);
		neg_apply(bag);
		while (bag->len_specifier-- > 0)
			write(1, "0", 1);
		if (bag->flag_m == 0)
			bag->accuracy = -2;
	}
	else
	{
		if (bag->flag_m == 0 && bag->len_specifier > bag->accuracy)
			bag->accuracy = 0;
	}
	free(tmp);
}

void	if_prec_zero(t_printf *bag)
{
	if (bag->flag_z == 1 && (bag->accuracy > -1))
		bag->flag_z = 0;
}
