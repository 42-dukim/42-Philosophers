/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:00:50 by dukim             #+#    #+#             */
/*   Updated: 2024/09/25 17:00:52 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_INTERNAL_H
# define GET_NEXT_LINE_INTERNAL_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				fd;
	char			*backup;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

char	*ft_strjoin(char *s1, char *s2, char end);
char	*ft_get_chridx(const char *s, int c);
t_list	*ft_lstnew(int fd);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	del_node(t_list **list, t_list *node);

char	*read_buffer(t_list	*node);
char	*split_buffer(char *buf, char **backup);
char	*get_one_line(t_list *node);

#endif
