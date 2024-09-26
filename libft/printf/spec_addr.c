/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_addr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 01:47:36 by dukim             #+#    #+#             */
/*   Updated: 2024/04/23 15:21:09 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

t_specifier	ft_putaddr(t_format *format, const void *addr)
{
	t_specifier	spec;
	t_specifier	tmp;

	ft_memset(&spec, 0, sizeof(t_specifier));
	if (!addr)
	{
		if (format->flag.precision && format->precision < 5)
		{
			spec.str = ft_strdup("");
			spec.len = 0;
			return (spec);
		}
		spec.str = ft_strdup("(nil)");
		spec.len = 5;
		return (spec);
	}
	tmp = ft_puthex(format, (unsigned long)addr, 1, 1);
	spec.str = ft_strjoin("0x", tmp.str);
	spec.len = 2 + tmp.len;
	free(tmp.str);
	return (spec);
}
