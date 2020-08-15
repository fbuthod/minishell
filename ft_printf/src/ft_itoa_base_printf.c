/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 15:53:46 by ksam              #+#    #+#             */
/*   Updated: 2020/02/19 11:58:18 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

char	*ft_base(enum e_base base)
{
	char	*str[3];

	str[0] = "0123456789";
	str[1] = "0123456789ABCDEF";
	str[2] = "0123456789abcdef";
	return (str[base]);
}

char	*ft_itoa_base(unsigned long long n, char *charset)
{
	char			*str;
	unsigned long	i;
	int				base;

	base = ft_strlen(charset);
	i = ft_length(n, base);
	if (!(str = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n != 0)
	{
		str[i] = charset[(n % base)];
		n = n / base;
		i--;
	}
	return (str);
}

int		ft_length(unsigned long long n, int base)
{
	unsigned long	i;

	i = 0;
	if (base < 0)
		base *= -1;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}
