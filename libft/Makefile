# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 13:04:15 by dukim             #+#    #+#              #
#    Updated: 2024/03/07 14:07:16 by dukim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
NAME		=	libft.a
GNL_DIR		=	gnl
PRINTF_DIR	=	printf

SRC			= 	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c\
				ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c\
				ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strnstr.c\
				ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c\
				ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c\
				ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c\
				ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c\
				ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c\
				ft_putendl_fd.c ft_putnbr_fd.c
LST_SRC		=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
				ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
				ft_lstmap.c
OBJS		=	$(SRC:.c=.o)
LST_OBJS	=	$(LST_SRC:.c=.o)

ifdef BONUS
	FINAL_OBJS = $(OBJS) $(LST_OBJS)
else
	FINAL_OBJS = $(OBJS)
endif

.PHONY:		all bonus clean fclean re

all:	$(NAME)

$(NAME):	$(FINAL_OBJS)
	@make -C $(GNL_DIR)
	@make -C $(PRINTF_DIR)
	ar -rc $(NAME) $(FINAL_OBJS) $(GNL_DIR)/*.o $(PRINTF_DIR)/*.o

$(OBJS):	$(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

$(LST_OBJS)	:	$(LST_SRC)
	$(CC) $(CFLAGS) -c $(LST_SRC)

bonus:
	@make BONUS=1 all

clean:
	@make clean -C $(GNL_DIR)
	@make clean -C $(PRINTF_DIR)
	@rm -f $(OBJS) $(LST_OBJS)

fclean:		clean
	@make fclean -C $(GNL_DIR)
	@make fclean -C $(PRINTF_DIR)
	@rm -f $(NAME)

re:			fclean all