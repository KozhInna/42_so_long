/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:14:19 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/01 22:43:37 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

void	convert_to_image(t_game *game, char *path, mlx_image_t **item)
{
	mlx_texture_t* texture;
	texture = mlx_load_png(path);
	if (!texture)
		exit(EXIT_FAILURE);

	(*item) = mlx_texture_to_image(game->mlx, texture);
	if (!item)
		exit(EXIT_FAILURE);
	// mlx_delete_texture(texture);
}

void	render_image(mlx_t *mlx, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(mlx, img, x, y) < 0)
		exit(EXIT_FAILURE);
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
			render_image(game->mlx, game->img_floor, j * 64, i * 64);
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
				render_image(game->mlx, game->img_wall, j * 64, i * 64);
			else if (map->map_data[i][j] == 'E')
				render_image(game->mlx, game->img_exit, j * 64, i * 64);
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
				render_image(game->mlx, game->img_player, j * 64, i * 64);
			else if (map->map_data[i][j] == 'C')
				render_image(game->mlx, game->img_collectible, j * 64, i * 64);
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


void	game_init(t_game *game, t_map *map)
{
	game->mlx = mlx_init(map->cols * 64, map->rows * 64, "42Balls", true);
	if (!game->mlx)
	{
		ft_putstr_fd("MLX failed to initialize\n", 2);
		exit(EXIT_FAILURE);
	}
	png_to_mlx(game);
	render_floor(game, map);
	render_walls(game, map);
	render_items(game, map);
}
