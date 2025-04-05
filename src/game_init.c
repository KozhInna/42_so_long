/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:14:19 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/05 14:09:22 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

void	convert_to_image(t_game *game, char *path, mlx_image_t **item)
{
	mlx_texture_t* texture;
	texture = mlx_load_png(path);
	if (!texture)
		exit(1);
	(*item) = mlx_texture_to_image(game->mlx, texture);
	if (!(*item))
		exit(1);
	mlx_delete_texture(texture);
}

void	png_to_mlx(t_game *game)
{
	convert_to_image(game, FLOOR, &game->img_floor);
	convert_to_image(game, WALL, &game->img_wall);
	convert_to_image(game, EXIT, &game->img_exit);
	convert_to_image(game, PLAYER, &game->img_player);
	convert_to_image(game, ITEM, &game->img_worm);
}
void initialise_struct(t_game *game)
{
	game->mlx = NULL;
	game->map = NULL;
	game->img_player = NULL;
	game->img_exit = NULL;
	game->img_worm = NULL;
	game->img_wall = NULL;
	game->img_floor = NULL;
	game->move_count = 0;
}

void	game_init(t_game *game, t_map *map)
{
	int32_t screen_width;
	int32_t screen_height;

	initialise_struct(game);
	game->map = map;
	game->mlx = mlx_init(map->cols * T_SIZE, map->rows * T_SIZE, "so_long", false);
	if (!game->mlx)
		error_exit("MLX failed to initialize\n", map);
	mlx_get_monitor_size(0, &screen_width, &screen_height);
	if (map->height > screen_height || map->width > screen_width)
		error_exit("Error\nMap is too big for the current monitor.\n", map);
	png_to_mlx(game);
	render_game(game, map);
}
