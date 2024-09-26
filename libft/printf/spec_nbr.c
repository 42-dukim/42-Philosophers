/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_nbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:43:50 by dukim             #+#    #+#             */
/*   Updated: 2024/04/23 15:25:00 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	pow_ten(unsigned int un)
{
	unsigned int	pow;

	if (un >= 1000000000)
		return (1000000000);
	pow = 1;
	while (pow <= un)
		pow *= 10;
	return (pow / 10);
}

static char	*make_zero_precision(int precision_len)
{
	char	*zero;

	if (precision_len <= 0)
	{
		zero = ft_strdup("");
		return (zero);
	}
	zero = (char *)malloc(precision_len + 1);
	ft_memset(zero, '0', precision_len);
	zero[precision_len] = '\0';
	return (zero);
}

static char	*make_nbr_str(int n, int sign_flag)
{
	char				nbr[12];
	unsigned int		pow;
	unsigned int		un;
	int					i;

	if (n == 0)
		return (ft_strdup("0"));
	i = 0;
	un = n;
	if (sign_flag && n < 0)
		un = -n;
	if (!sign_flag && n < 0)
		un = n + 2147483648 * 2;
	pow = pow_ten(un);
	while (pow)
	{
		nbr[i++] = (un / pow) + '0';
		un = un % pow;
		pow /= 10;
	}
	nbr[i] = '\0';
	return (ft_strdup(nbr));
}

static char	make_sign_ch(t_flag *flag, char sign_flag, char actual_flag)
{
	if (flag->precision)
		flag->zero = 0;
	if (flag->plus)
		flag->blank = 0;
	if (sign_flag && actual_flag && flag->blank)
	{
		flag->blank = 0;
		flag->plus = 1;
		return (' ');
	}
	if (sign_flag && !actual_flag)
		return ('-');
	return ('+');
}

t_specifier	ft_putnbr(t_format *format, int n, char sign_flag)
{
	t_specifier			spec;
	char				*zero;
	char				*nbr;

	ft_memset(&spec, 0, sizeof(t_specifier));
	spec.sign_ch = make_sign_ch(&(format->flag), sign_flag, n >= 0);
	nbr = make_nbr_str(n, sign_flag);
	if (*nbr == '0' && (format->flag.precision && !format->precision))
	{
		spec.str = ft_strdup("");
		spec.len = ft_strlen(spec.str);
		free(nbr);
		return (spec);
	}
	zero = make_zero_precision(format->precision - (int)ft_strlen(nbr));
	spec.str = ft_strjoin(zero, nbr);
	spec.len = ft_strlen(spec.str);
	free(nbr);
	free(zero);
	return (spec);
}
