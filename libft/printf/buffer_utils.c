/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:08:34 by dukim             #+#    #+#             */
/*   Updated: 2024/04/23 15:09:22 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

void	clean_buffer(t_buffer *buf, int *res)
{
	if (buf->len > 0)
	{
		write(1, buf->content, buf->len);
		*res += buf->len;
		buf->len = 0;
	}
}

void	store_buffer(t_buffer *buf, int *res, char ch)
{
	if (buf->len == 1024)
		clean_buffer(buf, res);
	buf->content[buf->len] = ch;
	buf->content[buf->len + 1] = '\0';
	(buf->len)++;
}
