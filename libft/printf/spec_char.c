/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:33:14 by dukim             #+#    #+#             */
/*   Updated: 2024/04/23 15:21:40 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

t_specifier	ft_putchar(const char ch)
{
	t_specifier	spec;
	char		str[2];

	ft_memset(&spec, 0, sizeof(t_specifier));
	str[0] = ch;
	str[1] = '\0';
	spec.str = ft_strdup(str);
	spec.len = 1;
	return (spec);
}
