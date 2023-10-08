# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 18:25:25 by ckannane          #+#    #+#              #
#    Updated: 2023/10/08 18:44:34 by ckannane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc

CFLAGS = -lmlx -framework Cocoa -framework OpenGL -framework IOKit

RM = rm -f

SRC = run.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJ_SRC = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ_SRC)
		$(CC) $(CFLAGS) libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(OBJ_SRC) libft/libft.a -o $(NAME)

clean :
		$(RM) $(OBJ_SRC)

fclean :
		$(RM) $(OBJ_SRC) $(NAME)

re: fclean all