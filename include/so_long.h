/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:49:20 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/05 14:20:26 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <MLX42/MLX42.h>
# define T_SIZE 100
# include "libft.h"
# include <fcntl.h>

/*delete lib below*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

# define WALL "./textures/coral.png"
# define FLOOR "./textures/water.png"
# define ITEM "./textures/worm.png"
# define PLAYER "./textures/player.png"
# define EXIT "./textures/cave.png"

typedef struct s_coords
{
	int x;
	int y;
} t_coords;

typedef struct s_map
{
	char **map_data;
	int rows;
	int cols;
	int collectibles;
	int width;
	int height;
	t_coords player;
	t_coords exit;
} t_map;

typedef struct game
{
	mlx_t *mlx;
	t_map *map;
	mlx_image_t *img_player;
	mlx_image_t *img_exit;
	mlx_image_t *img_worm;
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
void 	error_exit(char *message, t_map *map);
void	check_valid_player_position(t_map *map);
void	close_game(void *parameter);
int		flood_check(t_map *map, int (*func)(char **, t_map *, t_coords));
int		flood_fill_items(char **copy_map, t_map *map, t_coords player);
int		flood_fill_exit(char **copy_map, t_map *map, t_coords player);
void	render_game(t_game *game, t_map *map);

#endif
