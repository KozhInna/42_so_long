/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:25:43 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/31 14:59:09 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

void handle_move()
{
	printf("hello");
}

mlx_keyfunc	moves(mlx_key_data_t key, void *parameter)
{
	t_game *game;

	// int x;
	// int y;

	game = (t_game *) parameter;
	// x = game->map->pl_x;
	// y = game->map->pl_y;
	// key;
	// printf("here");
	// printf("x - %d, y -%d\n", x, y);
	// if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
	// 	close_game(game);
	if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
		handle_move();
		// x++;
		// handle_move(game, x + 1, y);
	// if (key.key == MLX_KEY_LEFT && key.action == MLX_PRESS)
	// 	x--;
	// 	// handle_move(game, x - 1, y);
	// if (key.key == MLX_KEY_DOWN && key.action == MLX_PRESS)
	// 	y++;
	// 	// handle_move(game, x, y + 1);
	// if (key.key == MLX_KEY_UP && key.action == MLX_PRESS)
	// 	y--;
		// handle_move(game, x, y - 1);
	return (0);
}