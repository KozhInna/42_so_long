/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:14:19 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/04 10:35:03 by ikozhina         ###   ########.fr       */
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
	if (!item)
		exit(1);
	mlx_delete_texture(texture);
}

void	render_image(mlx_t *mlx, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(mlx, img, x, y) < 0)
		exit(1);
}

void	render_floor(t_game *game, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			render_image(game->mlx, game->img_floor, j * T_SIZE, i * T_SIZE);
			j++;
		}
		i++;
	}
}
void	render_walls(t_game *game, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->map_data[i][j] == '1')
				render_image(game->mlx, game->img_wall, j * T_SIZE, i * T_SIZE);
			else if (map->map_data[i][j] == 'E')
				render_image(game->mlx, game->img_exit, j * T_SIZE, i * T_SIZE);
			j++;
		}
		i++;
	}
}

void	render_items(t_game *game, t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->map_data[i][j] == 'P')
				render_image(game->mlx, game->img_player, j * T_SIZE, i * T_SIZE);
			else if (map->map_data[i][j] == 'C')
				render_image(game->mlx, game->img_collectible, j * T_SIZE, i * T_SIZE);
			j++;
		}
		i++;
	}
}

void	png_to_mlx(t_game *game)
{
	convert_to_image(game, FLOOR, &game->img_floor);
	convert_to_image(game, WALL, &game->img_wall);
	convert_to_image(game, EXIT, &game->img_exit);
	convert_to_image(game, PLAYER, &game->img_player);
	convert_to_image(game, ITEM, &game->img_collectible);
}
void initialise_struct(t_game *game)
{
	game->mlx = NULL;
	game->map = NULL;
	game->img_player = NULL;
	game->img_exit = NULL;
	game->img_collectible = NULL;
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
	{
		ft_putstr_fd("MLX failed to initialize\n", 2);
		safe_exit(map);
		exit(1);
	}
	mlx_get_monitor_size(0, &screen_width, &screen_height);
	if (map->height > screen_height || map->width > screen_width)
	{
		ft_putstr_fd("Error\nMap is too big for the current monitor.\n", 1);
		safe_exit(map);
		exit(1);
	}
	png_to_mlx(game);
	render_floor(game, map);
	render_walls(game, map);
	render_items(game, map);
}
