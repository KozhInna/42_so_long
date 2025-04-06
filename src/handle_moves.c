/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:25:43 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/06 10:48:36 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_player_position(t_game *game, int new_x, int new_y)
{
	int x;
	int y;

	x = game->map->player.x;
	y = game->map->player.y;
	game->map->map_data[y][x] = '0';
	game->map->map_data[new_y][new_x] = 'P';
	game->map->player.x = new_x;
	game->map->player.y = new_y;
	game->img_player->instances[0].x = new_x * T_SIZE;
	game->img_player->instances[0].y = new_y * T_SIZE;
	game->move_count += 1;
	ft_printf("Current move: %d\n", game->move_count);
}
void	update_collectible(t_game *game, int new_x, int new_y)
{
	size_t	i;
	
	i = 0;
	while (i < game->img_worm->count)
	{
		if (game->img_worm->instances[i].x == new_x * T_SIZE &&
			game->img_worm->instances[i].y == new_y * T_SIZE)
			game->img_worm->instances[i].enabled = false;
		i++;
	}
	game->map->collectibles--;
}
void handle_move(t_game *game, int new_x, int new_y)
{
	char tile;

	tile = game->map->map_data[new_y][new_x];
	if (tile == '1')
		return ;
	if (tile == 'C')
		update_collectible(game, new_x, new_y);
	if (tile == '0' || tile == 'C')
		update_player_position(game, new_x, new_y);
	if (tile == 'E' && game->map->collectibles == 0)
	{
		safe_exit(game->map);
		ft_putstr_fd("Congratulations! You won!\n", 1);
		exit(0);
	}
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
	x = game->map->player.x;
	y = game->map->player.y;
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

