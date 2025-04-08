/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:49:20 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/08 14:23:40 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <fcntl.h>

# define T_SIZE 100
# define WALL "./textures/coral.png"
# define FLOOR "./textures/water.png"
# define ITEM "./textures/worm.png"
# define PLAYER "./textures/player.png"
# define EXIT "./textures/cave.png"

typedef struct s_coords
{
	int			x;
	int			y;
}				t_coords;

typedef struct s_map
{
	char		**map_data;
	int			rows;
	int			cols;
	int			collectibles;
	int			width;
	int			height;
	t_coords	player;
	t_coords	exit;
}				t_map;

typedef struct game
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*img_player;
	mlx_image_t	*img_exit;
	mlx_image_t	*img_worm;
	mlx_image_t	*img_wall;
	mlx_image_t	*img_floor;
	int			move_count;
}				t_game;

void			validate_argv(int argc, char **argv);
t_map			*validate_map(char *map_file);
t_map			*parse_map(char *map_file);
void			check_valid_player_position(t_map *map);
int				flood_check(t_map *map, int (*func)(char **, t_map *,
						t_coords));
int				flood_fill_items(char **copy_map, t_map *map, t_coords player);
int				flood_fill_exit(char **copy_map, t_map *map, t_coords player);
void			game_init(t_game *game, t_map *map);
void			render_game(t_game *game, t_map *map);
void			handle_click(mlx_key_data_t keydata, void *parameter);
void			close_game(void *parameter);
void			free_map(t_map *map);
void			free_game_img(t_game *game);
void			error_exit(char *msg, t_map *map);
void			error_close_game(char *msg, t_game *game, t_map *map);

#endif
