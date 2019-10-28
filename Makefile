# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/20 18:40:16 by gedemais          #+#    #+#              #
#    Updated: 2019/10/28 01:47:30 by demaisonc        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

OFLAGS = -O3 -Ofast -march=native

SRCS_NAME = main.c\
			parsing.c\
			read_file.c\
			ray_casting.c\
			deal_key.c\
			minimap.c\
			reticle.c\
			enemys.c\
			omniscience.c\
			math.c\
			z_lst.c\
			as_lst.c\
			weapons.c\
			load_sprites.c\
			mlx_fts.c

SRCS_PATH = srcs/

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS = $(SRCS_NAME:.c=.o)

MLX_PATH = minilibx_macos/

MLX = minilibx_macos/libmlx.a

MLX_OBJS_NAME = mlx_init_loop.o\
				mlx_int_str_to_wordtab.o\
				mlx_new_image.o\
				mlx_new_window.o\
				mlx_shaders.o\
				mlx_xpm.o

MLX_OBJS = $(addprefix $(MLX_PATH), $(MLX_OBJS_NAME))

LIB_PATH = libft/

LIB = libft/libft.a

INC_PATH = includes/

INC = includes/wolf3d.h

NAME = wolf3d

all : $(MLX_PATH) $(LIB) $(NAME) $(INC)

$(NAME) : $(MLX) $(INC) $(LIB_PATH) $(SRCS)
	@echo "Making $(RED)Wolfd3D...$(DEF)"
	@$(CC) $(CFLAGS) -o $(NAME) -I $(INC_PATH) -I minilibx_macos/ $(SRCS) -L minilibx_macos/ minilibx_macos/libmlx.a -framework OpenGL -framework AppKit -lpthread $(LIB)
	@echo "$(GRE)Done !$(DEF)"

$(LIB) :
	@echo "Making $(SOU)Libft$(DEF) :"
	@make -C libft/

$(MLX) : $(MLX_PATH)
	@echo "Making $(SOU)MinilibX$(DEF) :"
	@make -C $(MLX_PATH)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(MLX_OBJS)
	@make -C libft/ clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(OBJS)
	@rm -rf $(MLX_PATH)/libmlx.a
	@make -C libft/ fclean

re : fclean all
