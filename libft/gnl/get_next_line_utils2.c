/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:34:19 by dukim             #+#    #+#             */
/*   Updated: 2024/09/25 17:00:39 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_internal.h"

char	*read_buffer(t_list	*node)
{
	char	*buf;
	ssize_t	size;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	size = read(node->fd, buf, BUFFER_SIZE);
	if (size == -1)
	{
		free(buf);
		return (0);
	}
	buf[size] = '\0';
	return (buf);
}

char	*split_buffer(char *buf, char **backup)
{
	char	*res;

	res = ft_strjoin(*backup, buf, '\0');
	free(*backup);
	*backup = 0;
	if (*res == '\0')
	{
		free(res);
		return (0);
	}
	if (!ft_get_chridx(res, '\n'))
	{
		if (*buf == '\0')
			return (res);
		*backup = res;
		return (0);
	}
	buf = ft_strjoin("", res, '\n');
	*backup = ft_strjoin(ft_get_chridx(res, '\n') + 1, "", '\0');
	free(res);
	return (buf);
}

char	*get_one_line(t_list *node)
{
	char	*buf;
	char	*res;

	while (1)
	{
		buf = read_buffer(node);
		if (!buf)
			return (0);
		res = split_buffer(buf, &(node->backup));
		free(buf);
		if (!res &&!(node->backup))
			return (0);
		if (res)
			break ;
	}
	return (res);
}
