# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/27 17:54:59 by amufleh           #+#    #+#              #
#    Updated: 2025/11/05 12:59:49 by amufleh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	validation_path.c \
	check_boundaries.c \
	fill_the_map.c \

CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)
NAME = so_long.a
GNXL = get_next_line/getnextline.a
MINILBX = minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(GNXL) $(MINILBX)
	cp $(GNXL) $(NAME) $(MINILBX)
	ar rcs $(NAME) $(OBJ)

$(GNXL):
	make -C get_next_line

$(MINILBX):
	make -C minilibx-linux
clean:
	rm -f $(OBJ)
	make -C get_next_line clean

fclean: clean
	rm -f $(NAME)
	make -C get_next_line fclean
	make -C minilibx-linux clean

re: fclean $(NAME)

.PHONY: all clean fclean re

