/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_safe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:48:49 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/08 11:59:15 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_map *map)
{
	int	i;

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

void	error_close_game(char *msg, t_game *game, t_map *map)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	free_map(map);
	free_game_img(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
	exit(1);
}

void	error_exit(char *msg, t_map *map)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	free_map(map);
	exit(1);
}
