# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amufleh <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/27 17:54:59 by amufleh           #+#    #+#              #
#    Updated: 2025/10/27 17:55:26 by amufleh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)
NAME = solong.a
GNXL = get_next_line/getnextline.a

all: $(NAME)

$(NAME): $(OBJ) $(GNXL)
	cp $(GNXL) $(NAME)
	ar rcs $(NAME) $(OBJ)
$(GNXL):
	make -C get_next_line
clean:
	rm -f $(OBJ)
	make -C get_next_line clean

fclean: clean
	rm -f $(NAME)
	make -C get_next_line fclean

re : fclean $(NAME)


.PHONY : all clean fclean re

