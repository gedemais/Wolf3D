# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gedemais <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/20 18:40:16 by gedemais          #+#    #+#              #
#    Updated: 2019/11/19 11:44:31 by gedemais         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -g3 -fsanitize=address
endif

OPTI ?= 0
ifeq ($(OPTI), 1)
    CFLAGS += -O3 -Ofast -march=native
endif

SRCS_NAME = a_star.c\
            barre.c\
            bresenham.c\
            deal_key.c\
            enemys.c\
            game_over.c\
            load_sprites.c\
            main.c\
            math.c\
            minimap.c\
            mlx_fts.c\
            node_lst.c\
            omniscience.c\
            parsing.c\
            ray_casting.c\
            read_file.c\
            render_zombie.c\
			reticle.c\
			weapons.c\
			z_lst.c

SRCS_PATH = srcs/
SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_NAME = $(SRCS_NAME:.c=.o)
OBJS_PATH = objs/
OBJS = $(addprefix $(SRCS_PATH), $(OBJS_NAME))

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
INC = 	includes/wolf3d.h\
		includes/keys.h

NAME = wolf3d

all : $(MLX_PATH) $(LIB) $(NAME) $(INC)

$(NAME) : $(MLX) $(INC) $(LIB_PATH) $(OBJS_NAME)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_NAME) -I $(INC_PATH) -I $(MLX_PATH) $(MLX) -framework OpenGL -framework AppKit $(LIB)
	@echo "$(GRE)Done !$(DEF)"

%.o : $(SRCS_PATH)%.c $(INC)
	$(CC) $(CFLAGS) -c $< -I $(INC_PATH) -I $(MLX_PATH)

$(LIB) :
	@echo "Making $(SOU)Libft$(DEF) :"
	@make -C libft/

$(MLX) : $(MLX_PATH)
	@echo "Making $(SOU)MinilibX$(DEF) :"
	@make -C $(MLX_PATH)
	@echo "Making $(RED)Wolfd3D...$(DEF)"

clean:
	@rm -rf $(OBJS_NAME)
	@rm -rf $(MLX_OBJS)
	@rm -rf $(NAME).dSYM
	@make -C libft/ clean

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(MLX_PATH)/libmlx.a
	@make -C libft/ fclean

re : fclean all

.PHONY: all clean fclean re
