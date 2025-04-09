/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:51:03 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/09 10:53:57 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	*map;

	validate_argv(argc, argv);
	map = validate_map(argv[1]);
	if (!map)
		error_exit("Error\nMap validation failed\n", NULL);
	game_init(&game, map);
	mlx_close_hook(game.mlx, close_game, &game);
	mlx_key_hook(game.mlx, handle_click, &game);
	mlx_loop(game.mlx);
	return (0);
}
