/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:25:43 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/03 12:59:40 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

void handle_move(t_game *game, int new_x, int new_y)
{
	int x;
	int y;
	size_t	i;

	// printf("instances %zu\n", game->img_collectible->count);
	// printf("coll %d\n", game->map->collectibles);
	x = game->map->pl_x;
	y = game->map->pl_y;
	if (game->map->map_data[new_y][new_x] == '1')
		return ;
	if (game->map->map_data[new_y][new_x] == '0' ||
		game->map->map_data[new_y][new_x] == 'C')
	{
		if (game->map->map_data[new_y][new_x] == 'C')
		{
			i = 0;
			while (i < game->img_collectible->count)
			{
				if (game->img_collectible->instances[i].x == new_x * TILE_SIZE &&
					game->img_collectible->instances[i].y == new_y * TILE_SIZE)
					game->img_collectible->instances[i].enabled = false;
				i++;
			}
			game->map->collectibles--;
		}
		game->map->map_data[y][x] = '0';
		game->map->map_data[new_y][new_x] = 'P';
		game->map->pl_x = new_x;
		game->map->pl_y = new_y;
		game->img_player->instances[0].x = new_x * TILE_SIZE;
		game->img_player->instances[0].y = new_y * TILE_SIZE;
		game->move_count += 1;
		ft_printf("Current move: %d\n", game->move_count);
	}
	if (game->map->map_data[new_y][new_x] == 'E')
	{
		if (game->map->collectibles == 0)
		{
			safe_exit(game->map);
			ft_putstr_fd("Congratulations! You won!\n", 1);
			exit(0);
		}
		return ;
	}
	x = game->map->pl_x;
	y = game->map->pl_y;
	// printf("changed x - %d, y -%d\n", x, y);
}

void	close_game(void *parameter)
{
	t_game *game;

	game = (t_game *)parameter;
	if(game->mlx)
		mlx_terminate(game->mlx);
	safe_exit(game->map);
	exit(0);
}

void	handle_click(mlx_key_data_t keydata, void *parameter)
{
	t_game *game;
	int x;
	int y;

	game = (t_game *)parameter;
	x = game->map->pl_x;
	y = game->map->pl_y;
	// printf("x - %d, y -%d\n", x, y);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_game(game);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		handle_move(game, x, y - 1);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		handle_move(game, x, y + 1);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		handle_move(game, x - 1, y);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		handle_move(game, x + 1, y);
}