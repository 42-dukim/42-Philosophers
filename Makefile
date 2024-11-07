# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 20:45:58 by dukim             #+#    #+#              #
#    Updated: 2024/11/07 20:46:00 by dukim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I philo/inc
NAME 	= philo
SRCDIR  = src
INCDIR  = inc
SRCS    = end_handler.c main.c parse_arg.c print_phio.c utils.c fork.c monitoring.c philo.c routine.c
SRCS 	:=	$(SRCS:%=$(SRCDIR)/%)
OBJS 	:=	$(SRCS:%.c=%.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS)	:	$(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
	@mv *.o $(SRCDIR)

clean:
	@rm -f $(OBJS)

fclean:		clean
	@rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
