# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/06 14:15:36 by earnaud           #+#    #+#              #
#    Updated: 2021/03/26 16:22:44 by earnaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
CC			= gcc
OS 				:=	$(shell uname)
CFLAGS		= -g #-Wall -Wextra -Werror
OPENGL		= -lmlx -lXext -lX11 -lm
INCLUDES	= -Iincludes/ -I$(MINILIBX_DIR)
OBJ_DIR		= obj/
SRCS_DIR 	= srcs/
NEED		= dependencies/libft

NEEDA		= $(NEED)/*.a

ifeq ($(OS), Linux)
	MINILIBX_DIR = dependencies/mlx_linux
	OPENGL = -lm -lbsd -lX11 -lXext
endif
ifeq ($(OS), Darwin)
	MINILIBX_DIR = dependencies/mlx_opengl
	OPENGL = -lz -framework OpenGL -framework AppKit
endif
MINILIBX_A_DIR 		=	$(MINILIBX_DIR)/libmlx.a

FILES		=  get_next_line.c \
				get_next_line_utils.c \
				main.c \
				mlx_util.c \
				colors.c \
				littlemath.c\
				littlemath2.c \
				littlemath3.c \
				littlemath4.c \
				shapes.c \
				matrice.c \
				ray.c \
				lights.c \
				planes.c \
				triangles.c \
				spheres.c \
				squares.c \
				cylinders.c \
				parsfile.c \
				parscam.c \
				pars_light.c \
				pars_sphere.c \
				pars_plane.c \
				pars_triangle.c \
				pars_square.c \
				pars_cylinder.c \
				filters.c \
				bmp.c \
				bmp_util.c \
				color2.c


SRCS		= $(addprefix $(SRCS_DIR), $(FILES))
OBJ			= $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ) dependencies
		@echo MiniRT on the way...
		@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES)\
		 $(MINILIBX_A_DIR) $(NEEDA) $(OPENGL) \
		-o $(NAME)
		@echo success

dependencies :
		@echo building dependencies
		make -C $(NEED)
		make -C $(MINILIBX_DIR)
		@echo dependencies success

clean:
		make clean -C $(NEED)
		make clean -C $(MINILIBX_DIR)
		rm -f $(OBJ)
		@echo clean done
		
fclean: clean
		make fclean -C $(NEED)
		rm -f $(MINILIBX_A_DIR)
		rm -f $(NAME)
		@echo fclean done

re: fclean all

.PHONY: clean fclean all re dependencies
