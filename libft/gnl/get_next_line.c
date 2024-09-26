/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:34:12 by dukim             #+#    #+#             */
/*   Updated: 2024/06/28 13:34:14 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_internal.h"

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*node;
	char			*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	node = list;
	while (node)
	{
		if (node->fd == fd)
			break ;
		node = node->next;
	}
	if (!node)
	{
		node = ft_lstnew(fd);
		ft_lstadd_back(&list, node);
	}
	res = get_one_line(node);
	if (!res)
		del_node(&list, node);
	return (res);
}
