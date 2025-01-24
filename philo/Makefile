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
CFLAGS  = -Wall -Wextra -Werror -I inc
NAME 	= philo
SRCDIR  = src
INCDIR  = inc
SRCS    = main.c parser_arg.c utils.c fork.c philo.c philo_action.c philo_stat.c monitor.c
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
