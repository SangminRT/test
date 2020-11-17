# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanhan <sanhan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 13:35:39 by sanhan            #+#    #+#              #
#    Updated: 2020/11/17 19:42:30 by sanhan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

SRCS	=	srcs/main.c \
			srcs/init.c \
			srcs/bmp.c \
			srcs/cub_parse.c \
			srcs/cub_parse_nswe.c \
			srcs/cub_parse_rsfc.c \
			srcs/cub_parse_map.c \
			srcs/cub_init_player.c \
			srcs/key_wsad.c \
			srcs/key_arrow.c \
			srcs/map_check.c \
			srcs/error.c \
			srcs/util.c \
			srcs/raycasting_wall.c \
			srcs/raycasting_sprite.c \
			srcs/get_next_line_bonus.c \
			srcs/get_next_line_utils_bonus.c \

OBJS	=	${SRCS:%.c=%.o}

FLAGS	=	-Wall -Wextra -Werror
LEAKS	=	-g3 -fsanitize=address -fsanitize=undefined -std=c99

MLX		=	-Llibs/mlx -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) re -C ./libs/libft
	@$(MAKE) re -C ./libs/mlx
	gcc $(FLAGS) $(OBJS) -I./includes $(MLX) ./libs/libft/libft.a -o $(NAME)

clean :
	@$(MAKE) clean -C ./libs/libft
	@$(MAKE) clean -C ./libs/mlx
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)
	@$(MAKE) clean -C ./libs/mlx
	@$(MAKE) -C ./libs/libft fclean
	rm -rf screenshot.bmp

re : fclean all
