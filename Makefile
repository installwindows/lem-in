# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/30 22:20:02 by varnaud           #+#    #+#              #
#    Updated: 2017/06/02 06:31:46 by varnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
SRC = main.c \
	  validate.c \
	  p.c

OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -g -Wall -Wextra -Ilibft

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAG) -o $(NAME) $(OBJ) -Llibft -lft

$(OBJ): lem_in.h

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all
