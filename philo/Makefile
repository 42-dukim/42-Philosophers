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
OBJDIR  = obj
SRCS    = main.c parser_arg.c utils.c fork.c philo.c philo_action.c philo_stat.c monitor.c
SRCS 	:=	$(SRCS:%=$(SRCDIR)/%)
OBJS 	:=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/ft_philo.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)

fclean:		clean
	@rm -f $(NAME)

re:			fclean all

dev:
	$(MAKE) CC=clang CFLAGS="$(CFLAGS) -O0 -g3 -DDEBUG -fsanitize=thread -fno-omit-frame-pointer" re

.PHONY: all clean fclean re dev
