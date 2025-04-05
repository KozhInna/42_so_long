/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:11:08 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/05 11:29:35 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_duplicates(t_map *map)
{
	int i;
	int j;
	int player;
	int out;

	player = 0;
	out = 0;
	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->map_data[i][j])
		{
			if (map->map_data[i][j] == 'E')
				out++;
			if (map->map_data[i][j] == 'P')
				player++;
			j++;
		}
		i++;
	}
	if (player != 1 || out != 1 || map->collectibles < 1)
		error_exit("Error\nMap must contain exactly 1 exit, 1 player and at least 1 collectible\n", map);
}

void	check_valid_player_position(t_map *map)
{
	int collected;
	int exit_reached;

	check_duplicates(map);
	collected = flood_check(map, flood_fill_items);
	if (collected != map->collectibles)
		error_exit("Error\nCan't collect all worms.\n", map);
	exit_reached = flood_check(map, flood_fill_exit);
	if (!exit_reached)
		error_exit("Error\nPath to the exit is not valid.\n", map);
}
