# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dukim <dukim@student.42gyeonsan.kr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 17:54:40 by dukim             #+#    #+#              #
#    Updated: 2024/04/11 17:54:44 by dukim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

SRC		= 	ft_printf.c format.c buffer_utils.c print_utils.c\
			spec_char.c spec_str.c spec_nbr.c spec_hex.c spec_addr.c
OBJS	=	$(SRC:.c=.o)

.PHONY:		all clean fclean re

all		:	$(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

$(OBJS)	:	$(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	@rm -f $(OBJS)

fclean:		clean
	@rm -f $(NAME)

re:			fclean all
