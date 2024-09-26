/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:55:01 by dukim             #+#    #+#             */
/*   Updated: 2024/04/24 15:36:26 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	get_digit(int num)
{
	int	digit;

	digit = 0;
	while (num)
	{
		num /= 10;
		digit++;
	}
	return (digit);
}

static t_flag	make_flag(char **str)
{
	t_flag	flag;

	ft_memset(&flag, 0, sizeof(t_flag));
	while (**str == '+' || **str == '-' || **str == '0' \
						|| **str == '#' || **str == ' ')
	{
		if (**str == '+')
			flag.plus = 1;
		if (**str == '-')
			flag.minus = 1;
		if (**str == '0')
			flag.zero = 1;
		if (**str == '#')
			flag.sharp = 1;
		if (**str == ' ')
			flag.blank = 1;
		(*str)++;
	}
	return (flag);
}

static void	set_flag(t_format *format)
{
	if (!format->spec.str || \
		format->width > 2147483647 || format->precision > 2147483647)
		format->flag.error = 1;
	if (format->spec.sign_ch == '-')
		format->flag.plus = 1;
	if (format->specifier != 'd' && format->specifier != 'i')
		format->flag.plus = 0;
	if (format->flag.zero && format->flag.minus)
		format->flag.zero = 0;
}

t_specifier	make_specifier(t_format *format, char specifier, va_list args)
{
	t_specifier	spec;

	ft_memset(&spec, 0, sizeof(t_specifier));
	if (specifier == 'c')
		spec = ft_putchar(va_arg(args, int));
	if (specifier == 's')
		spec = ft_putstr(format, va_arg(args, char *));
	if (specifier == 'd' || specifier == 'i' || specifier == 'u')
		spec = ft_putnbr(format, va_arg(args, int), specifier != 'u');
	if (specifier == 'p')
		spec = ft_putaddr(format, va_arg(args, void *));
	if (specifier == 'X' || specifier == 'x')
		spec = ft_puthex(format, va_arg(args, unsigned int), \
										specifier == 'x', 0);
	if (specifier == '%')
	{
		ft_memset(&(format->flag), 0, sizeof(t_flag));
		format->precision = 0;
		format->width = 0;
		spec = ft_putchar('%');
	}
	return (spec);
}

t_format	make_format(char *str, va_list args)
{
	t_format	format;
	const char	*ori_s;

	ori_s = str;
	ft_memset(&format, 0, sizeof(t_format));
	format.flag = make_flag(&str);
	format.width = ft_atoi(str);
	str += get_digit(format.width);
	if (*str == '.')
	{
		str++;
		format.flag.precision = 1;
	}
	format.precision = ft_atoi(str);
	if (*str == '0')
		str++;
	str += get_digit(format.precision);
	format.specifier = *str;
	format.spec = make_specifier(&format, format.specifier, args);
	format.size = str - ori_s;
	set_flag(&format);
	return (format);
}
