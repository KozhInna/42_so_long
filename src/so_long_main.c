/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:51:03 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/31 14:55:48 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
	t_game	game;
	t_map	*map;

	validate_argv(argc, argv);

	printf("here1");
	map = validate_map(argv[1]);
	if (!map)
		exit(EXIT_FAILURE);
	game.map = map;
	printf("here");
	game_init(&game, map);
	// render_board(game, map);
	// game.img_wall->instances->x = new_x * 64;


	// mlx_close_hook(game.mlx, handle_close, &game);

	mlx_key_hook(game.mlx, moves, &game);
	mlx_loop(game.mlx);
	return (0);
}
