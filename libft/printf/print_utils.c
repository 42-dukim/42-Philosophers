/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:05:26 by dukim             #+#    #+#             */
/*   Updated: 2024/09/25 19:05:27 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

void	print_width(int width, int zero_flag)
{
	char	*buffer;
	char	ch;

	if (width <= 0)
		return ;
	buffer = (char *)malloc(sizeof(char) * width);
	ch = ' ';
	if (zero_flag)
		ch = '0';
	ft_memset(buffer, ch, width);
	write(1, buffer, width);
	free(buffer);
}

void	print_final_format(t_format format)
{
	if (!format.flag.minus)
	{
		if (format.flag.zero && format.flag.plus)
			ft_putchar_fd(format.spec.sign_ch, 1);
		print_width(format.width - format.spec.len - (format.flag.plus != 0), \
														format.flag.zero);
		if (!format.flag.zero && format.flag.plus)
			ft_putchar_fd(format.spec.sign_ch, 1);
		write(1, format.spec.str, format.spec.len);
	}
	if (format.flag.minus)
	{
		if (format.flag.plus)
			ft_putchar_fd(format.spec.sign_ch, 1);
		write(1, format.spec.str, format.spec.len);
		print_width(format.width - format.spec.len - (format.flag.plus != 0), \
														format.flag.zero);
	}
}

int	print_format(char **str, va_list args, int *res)
{
	t_format	format;

	(*str)++;
	if (**str == '\0')
		return (0);
	format = make_format(*str, args);
	if (format.flag.error == 1)
		return (0);
	*str += format.size + 1;
	if (format.width <= format.spec.len + (format.flag.plus != 0))
		*res += (format.flag.plus != 0) + format.spec.len;
	else
		*res += format.width;
	print_final_format(format);
	free(format.spec.str);
	return (1);
}
