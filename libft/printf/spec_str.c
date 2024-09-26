/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:54:04 by dukim             #+#    #+#             */
/*   Updated: 2024/04/23 15:22:41 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

t_specifier	ft_putstr(t_format *format, const char *str)
{
	t_specifier	spec;

	ft_memset(&spec, 0, sizeof(t_specifier));
	if (!str)
	{
		if (format->flag.precision && format->precision < 6)
		{
			spec.str = ft_strdup("");
			spec.len = 0;
			return (spec);
		}
		spec.str = ft_strdup("(null)");
		spec.len = 6;
		return (spec);
	}
	spec.len = ft_strlen(str);
	if (format->flag.precision \
		&& format->precision < (unsigned int)ft_strlen(str))
		spec.len = format->precision;
	spec.str = ft_substr(str, 0, spec.len);
	return (spec);
}
