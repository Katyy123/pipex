# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 13:44:56 by cfiliber          #+#    #+#              #
#    Updated: 2021/11/16 15:56:26 by cfiliber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIB_PATH = ./libft/

LIB = $(LIB_PATH)libft.a

SRCS = \
		pipex.c\
		execute.c\
		error.c\

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -I libft

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: subsystem $(NAME)

subsystem:
	make all -C $(LIB_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

clean:
	make clean -C $(LIB_PATH)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIB_PATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
