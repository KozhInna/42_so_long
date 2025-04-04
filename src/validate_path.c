/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:11:08 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/04 14:45:45 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_valid_player_position(t_map *map)
{
	int collected;
	int exit_reached;

	collected = flood_check(map, flood_fill_items);
	if (collected != map->collectibles)
	{
		ft_putstr_fd("Error\nCan't collect all worms.\n", 2);
		safe_exit(map);
		exit(1);
	}
	exit_reached = flood_check(map, flood_fill_exit);
	if (!exit_reached)
	{
		ft_putstr_fd("Error\nPath to the exit is not valid.\n", 2);
		safe_exit(map);
		exit(1);
	}
}
