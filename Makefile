# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/27 17:54:59 by amufleh           #+#    #+#              #
#    Updated: 2025/12/04 12:30:57 by amufleh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	validation_map.c \
	check_boundaries.c \
	fill_the_map.c \
	put_image.c \
	tools.c \
	tools2.c \
	minilibx.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)
NAME = so_long
GNL = get_next_line/getnextline.a
MLX = -lmlx -lXext -lX11

all: $(NAME)
$(NAME): $(OBJ) $(GNL)
	$(CC) $(CFLAGS) $(OBJ) $(GNL) $(MLX) -o $(NAME)

$(GNL):
	make -C get_next_line

clean:
	rm -f $(OBJ)
	make -C get_next_line clean

fclean: clean
	rm -f $(NAME)
	make -C get_next_line fclean

re: fclean all

.PHONY: all clean fclean re

