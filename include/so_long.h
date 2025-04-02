/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:49:20 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/02 13:23:55 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../MLX42/include/MLX42/MLX42.h"
# define WIDTH 800
# define HEIGHT 600
# define TILE_SIZE 100
# include "libft.h"
# include <fcntl.h>

/*delete lib below*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

# define WALL "./textures/coral_100.png"
# define FLOOR "./textures/water_100.png"
# define ITEM "./textures/worm_100.png"
# define PLAYER "./textures/player_100.png"
# define EXIT "./textures/cave_100.png"

typedef struct s_map
{
	char **map_data;
	int rows;
	int cols;
	int collectibles;
	int width;
	int height;
	int pl_x;
	int pl_y;
} t_map;

typedef struct game
{
	mlx_t *mlx;
	t_map *map;
	mlx_image_t *img_player;
	mlx_image_t *img_exit;
	mlx_image_t *img_collectible;
	mlx_image_t *img_wall;
	mlx_image_t *img_floor;
	int	move_count;
} t_game;

void	validate_argv(int argc, char **argv);
t_map	*validate_map(char *map_file);
t_map	*parse_map(char *map_file);
void	game_init(t_game *game, t_map *map);
void	handle_click(mlx_key_data_t keydata, void *parameter);
void	safe_exit(t_map *map);
void	render_image(mlx_t *mlx, mlx_image_t *img, int x, int y);
void	convert_to_image(t_game *game, char *path, mlx_image_t **item);
void	close_game(void *parameter);

#endif
