/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeonsan.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:41:00 by dukim             #+#    #+#             */
/*   Updated: 2024/04/23 15:07:37 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"

int	ft_printf(const char *str, ...)
{
	va_list		args;
	t_buffer	buf;
	int			res;

	va_start(args, str);
	buf.len = 0;
	res = 0;
	while (*str != '\0')
	{
		if (*str != '%')
		{
			store_buffer(&buf, &res, *str);
			str++;
			continue ;
		}
		clean_buffer(&buf, &res);
		if (!print_format((char **)&str, args, &res))
		{
			va_end(args);
			return (-1);
		}
	}
	va_end(args);
	clean_buffer(&buf, &res);
	return (res);
}
