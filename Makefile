# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/04 18:25:25 by ckannane          #+#    #+#              #
#    Updated: 2023/11/17 01:44:56 by ckannane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

NAME_BNS = cub3D_bns

CC = gcc

CFLAGS =  -O3 #-fsanitize=address -g

RM = rm -f 

FILE = ray_casting/run.c ray_casting/render.c

FILE_BNS = cub3d_bonus/run.c

SRC = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
parsing/map_pars.c parsing/utils_2.c parsing/check_numbers.c parsing/map_check.c parsing/map_check_utils.c parsing/utils.c ray_casting/moves.c ray_casting/cub3d_utiles.c \
ray_casting/render_textures.c ray_casting/rays.c ray_casting/cub3d_utils_2.c ray_casting/cub3d_utils_3.c ray_casting/free.c

OBJ_SRC = $(SRC:.c=.o) $(FILE:.c=.o)

OBJ_SRC_BNS = $(SRC:.c=.o) $(FILE_BNS:.c=.o)

.SILENT:

all : $(NAME)

bonus : $(NAME_BNS)

$(NAME) : $(OBJ_SRC)
		printf "\033[32mcompiling...\033[0m\n"
		$(CC) $(CFLAGS) libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(OBJ_SRC) libft/libft.a -o $(NAME)
		printf "\033[32mDONE\033[0m\n"

$(NAME_BNS) : $(OBJ_SRC_BNS)
		printf "\033[32mcompiling...\033[0m\n"
		$(CC) $(CFLAGS) libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(OBJ_SRC_BNS) libft/libft.a -o cub3d_bns
		printf "\033[32mDONE\033[0m\n"

clean :
		$(RM) $(OBJ_SRC)

fclean :
		$(RM) $(OBJ_SRC) $(NAME)
		printf "\033[31mcleaning...\033[0m\n"
		
clean_bonus :
		$(RM) $(OBJ_SRC_BNS)

fclean_bonus :
		$(RM) $(OBJ_SRC_BNS) $(NAME_BNS)
		printf "\033[31mcleaning...\033[0m\n"


re: fclean all

bonus_re: fclean_bonus bonus