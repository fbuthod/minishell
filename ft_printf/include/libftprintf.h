/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:00:21 by ksam              #+#    #+#             */
/*   Updated: 2020/03/06 00:02:01 by ksam             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>

# define SPEC_CSPP  "csp%"
# define SPEC_DIUX  "diuxX"

typedef struct		s_printf
{
	size_t			index;
	int				count;
	int				len_specifier;
	int				accuracy;
	int				width;
	long long		tmp;
	int				neg;
	int				min;
	int				flag_z;
	int				flag_m;
	int				flag_s;
	char			*spec;
}					t_printf;

enum				e_base
{
	BASE10 = 0,
	BASE16MA = 1,
	BASE16mi = 2
};

int					ft_printf(const char *string,
					...) __attribute__((format(printf,1,2)));
void				ft_struct_initialize(t_printf *list);
void				ft_struct_reinitialize(t_printf *bag);
void				reset_flag(t_printf *bag);
char				*ft_identifier(const char *str);
int					ft_printf_with_arg(va_list *ap, t_printf *bag,
					const char *s);
int					ft_convert(va_list *ap, t_printf *bag);
int					select_specifier(va_list *ap, t_printf *bag, char *ptr);
int					ft_width(va_list *ap, t_printf *bag);
void				ft_apply_width(t_printf *bag, int len);
void				ft_write_width(t_printf *bag);
void				ft_format_width_as_negative(t_printf *bag);
int					ft_precision(va_list *ap, t_printf *bag);
void				ft_apply_precision(t_printf *bag, long long specifier);
void				ft_convert_c(t_printf *bag, va_list *ap);
void				ft_convert_s(t_printf *bag, va_list *ap);
void				ft_convert_percent(t_printf *bag);
int					ft_convert_di(t_printf *bag, va_list *ap);
int					ft_convert_u(t_printf *bag, va_list *ap);
int					ft_convert_p(t_printf *bag, va_list *ap);
int					ft_convert_xx(t_printf *bag, va_list *ap);
char				*detect_specifier_x(t_printf *bag);
int					ft_convert_part_one(va_list *ap, t_printf *bag);
int					ft_convert_part_two(va_list *ap, t_printf *bag);
void				no_prec_no_specifier_(t_printf *bag, char *buffer);
void				ft_increase_index_spec(t_printf *bag, int nb);
void				ft_print_char(t_printf *bag, char c);
void				ft_update_count_and_more(t_printf *bag, char *buffer);
int					ft_count(long n);
void				ft_is_accuracy(t_printf *bag, char *buffer);
int					ft_calcul(t_printf *bag, va_list *ap);
char				*ft_itoa_base(unsigned long long n, char *charset);
int					ft_length(unsigned long long n, int base);
char				*ft_base(enum e_base base);
void				neg_apply(t_printf *bag);
int					neg_creat(t_printf *bag, int specifier);
void				ft_bag_initialize_s(t_printf *bag);
void				if_di_is_int_min(char *buffer, t_printf *bag);
void				if_prec_zero(t_printf *bag);
void				width_without_minus(char *buffer, int specifier_di,
					t_printf *bag);
int					main(int ac, char **av);
#endif
