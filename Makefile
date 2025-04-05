# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/21 14:44:32 by ikozhina          #+#    #+#              #
#    Updated: 2025/04/05 11:25:26 by ikozhina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc

FLAGS = -Werror -Wextra -Wall -I./libft -I./include -I./MLX42/include -Wunreachable-code -Ofast
LDFLAGS = -lglfw -L"/opt/homebrew/Cellar/glfw/3.4/lib/" -framework Cocoa -framework OpenGL -framework IOKit
# LDFLAGS = -ldl -lglfw -pthread -lm

MLX_PATH = ./MLX42
MLX_REPO = https://github.com/codam-coding-college/MLX42.git

SRCS = src/so_long_main.c src/validate_argv.c src/validate_map.c \
		src/parse_map.c src/game_init.c src/handle_moves.c src/validate_path.c \
		src/flood_check.c src/exit_safe.c

OBJS = $(SRCS:.c=.o)

MLXLIB = MLX42/build/libmlx42.a
LIBFT = libft/libft.a
LIBFT_PATH = libft


all: $(LIBFT) $(MLXLIB) $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLXLIB)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) $(MLXLIB) $(LDFLAGS) -o $(NAME)

#Clone and build MLX42
$(MLXLIB): $(MLX_PATH)
	cmake -B $(MLX_PATH)/build -S $(MLX_PATH) -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF
	cmake --build $(MLX_PATH)/build

$(MLX_PATH):
	git clone $(MLX_REPO) $(MLX_PATH)

mlx_update:
	@if [ -d "$(MLX_PATH)" ]; then \
		echo "Updating MLX42..."; \
		cd $(MLX_PATH) && git pull && \
		cmake -B build -S . -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF && \
		cmake --build build; \
	else \
		echo "MLX42 not found. Run 'make' to clone and build."; \
	fi

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf $(MLX_PATH)/build

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -rf $(MLX_PATH)

re:	fclean all

.PHONY: all clean fclean re mlx_update
