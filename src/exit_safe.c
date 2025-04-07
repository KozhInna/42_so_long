/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_safe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:48:49 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/07 14:52:55 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map *map)
{
	int i;

	i = 0;
	if (!map)
		return ;
	while (i < map->rows)
	{
		free(map->map_data[i]);
		map->map_data[i] = NULL;
		i++;
	}
	free(map->map_data);
	map->map_data = NULL;
	free(map);
}

void	free_game_img(t_game *game)
{
	if (game->img_exit)
		mlx_delete_image(game->mlx, game->img_exit);
	if (game->img_floor)
		mlx_delete_image(game->mlx, game->img_floor);
	if (game->img_player)
		mlx_delete_image(game->mlx, game->img_player);
	if (game->img_wall)
		mlx_delete_image(game->mlx, game->img_wall);
	if (game->img_worm)
		mlx_delete_image(game->mlx, game->img_worm);
}

void error_exit(char *message, t_map *map)
{
	ft_putstr_fd(message, 2);
	free_map(map);
	exit(1);
}