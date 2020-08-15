/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:31:57 by ksam              #+#    #+#             */
/*   Updated: 2020/02/16 00:45:51 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

int		ft_calcul(t_printf *bag, va_list *ap)
{
	int		ret;
	int		i;
	char	*buffer;

	ret = 0;
	i = 0;
	buffer = NULL;
	if (bag->spec[0] == '*')
	{
		ft_increase_index_spec(bag, 1);
		bag->tmp = va_arg(*ap, int);
		return (1);
	}
	while ((ret = ft_isdigit(bag->spec[i])))
		i++;
	bag->index += i;
	if (!(buffer = ft_calloc((i + 1), sizeof(char))))
		return (-1);
	buffer = ft_memcpy(buffer, bag->spec, i);
	bag->spec += i;
	bag->tmp = ft_atoi(buffer);
	free(buffer);
	return (1);
}

int		select_specifier(va_list *ap, t_printf *bag, char *ptr)
{
	int		ret;

	ret = 0;
	if (!(ptr = ft_strchr(SPEC_CSPP, bag->spec[0])))
	{
		if (!(ret = ft_convert_part_two(ap, bag)))
			return (-1);
	}
	else
	{
		if (!(ret = ft_convert_part_one(ap, bag)))
			return (-1);
	}
	return (ret);
}

void	no_prec_no_specifier_(t_printf *bag, char *buffer)
{
	ft_write_width(bag);
	write(1, "NullBitch", 0);
	buffer[0] = '\0';
	if (bag->width > -1 && bag->flag_m > 0)
		bag->width++;
}

void	ft_update_count_and_more(t_printf *bag, char *buffer)
{
	bag->count += ft_strlen(buffer);
	if ((bag->width > 0) && (bag->flag_m > 0))
		ft_apply_width(bag, ft_strlen(buffer));
	free(buffer);
}

void	ft_print_char(t_printf *bag, char c)
{
	if ((bag->width > 0) && (bag->flag_m == 0))
		ft_apply_width(bag, 1);
	write(1, &c, 1);
	if ((bag->width > 0) && (bag->flag_m > 0))
		ft_apply_width(bag, 1);
	bag->count++;
}
