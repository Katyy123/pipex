# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 13:44:56 by cfiliber          #+#    #+#              #
#    Updated: 2021/11/15 17:56:06 by cfiliber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIB_PATH = libft/

LIB = $(LIB_PATH)libft.a

SRCS = \
		pipex.c\
		utils.c\

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: subsystem $(NAME)

subsystem:
	make -C $(LIB_PATH) all

%.o : %.c
	$(CC) $(CFLAGS) -c -g $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

clean:
						make -C $(LIB_PATH) clean
						rm -f $(OBJS)

fclean: clean
						make -C $(LIB_PATH) fclean
						rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
