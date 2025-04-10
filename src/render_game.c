/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:50:50 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/08 11:59:26 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_img(t_game *game, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(game->mlx, img, x, y) < 0)
		error_close_game("Image rendering failed\n", game, game->map);
}

void	render_floor(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			render_img(game, game->img_floor, j * T_SIZE, i * T_SIZE);
			j++;
		}
		i++;
	}
}

void	render_walls(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->map_data[i][j] == '1')
				render_img(game, game->img_wall, j * T_SIZE, i * T_SIZE);
			else if (map->map_data[i][j] == 'E')
				render_img(game, game->img_exit, j * T_SIZE, i * T_SIZE);
			j++;
		}
		i++;
	}
}

void	render_objects(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (map->map_data[i][j] == 'P')
				render_img(game, game->img_player, j * T_SIZE, i * T_SIZE);
			else if (map->map_data[i][j] == 'C')
				render_img(game, game->img_worm, j * T_SIZE, i * T_SIZE);
			j++;
		}
		i++;
	}
}

void	render_game(t_game *game, t_map *map)
{
	render_floor(game, map);
	render_walls(game, map);
	render_objects(game, map);
}
