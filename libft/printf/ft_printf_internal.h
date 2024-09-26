/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeonsan.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:29:50 by dukim             #+#    #+#             */
/*   Updated: 2024/09/25 19:05:22 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include <stdarg.h>
# include "../libft.h"

typedef struct s_buffer
{
	char			content[1024];
	unsigned int	len;
}				t_buffer;

typedef struct s_flag
{
	char		plus;
	char		minus;
	char		zero;
	char		sharp;
	char		blank;
	char		precision;
	char		error;
}				t_flag;

typedef struct s_specifier
{
	char			*str;
	char			sign_ch;
	unsigned int	len;
}				t_specifier;

typedef struct s_format
{
	char			specifier;
	unsigned int	width;
	unsigned int	precision;
	unsigned int	size;
	t_flag			flag;
	t_specifier		spec;
}				t_format;

void		clean_buffer(t_buffer *buf, int *res);
void		store_buffer(t_buffer *buf, int *res, char ch);

t_specifier	ft_putchar(const char ch);
t_specifier	ft_putstr(t_format *format, const char *str);
t_specifier	ft_putnbr(t_format *format, int n, char sign_flag);
t_specifier	ft_puthex(t_format *format, unsigned long n, \
							char case_flag, char addr_flag);
t_specifier	ft_putaddr(t_format *format, const void *addr);

t_format	make_format(char *str, va_list args);

void		print_width(int width, int zero_flag);
void		print_final_format(t_format format);
int			print_format(char **str, va_list args, int *res);

#endif
