/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:11:08 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/04 13:02:19 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		flood_fill_exit(char **copy_map, t_map *map, t_coords player, t_coords exit)
{
	int found;
	int x;
	int y;
	int x2;
	int y2;

	x = player.x;
	y = player.y;
	x2 = exit.x;
	y2 = exit.y;
	if (x == x2 && y == y2)
		return (1);
	if (x < 0 || y < 0 || y >= map->rows || x >= map->cols
		|| copy_map[y][x] == '1' || copy_map[y][x] == 'V')
		return (0);
	copy_map[y][x] = 'V';
	found = (flood_fill_exit(copy_map, map, (t_coords){x + 1, y}, exit) ||
			flood_fill_exit(copy_map, map, (t_coords){x - 1, y}, exit) ||
			flood_fill_exit(copy_map, map, (t_coords){x, y + 1}, exit) ||
			flood_fill_exit(copy_map, map, (t_coords){x, y - 1}, exit));
	return (found);
}

int	flood_fill_items(char **copy_map, t_map *map, t_coords player)
{
	int found;
	int x;
	int y;

	found = 0;
	x = player.x;
	y = player.y;
	if (x < 0 || x >= map->cols || y < 0 || y >= map->rows ||
		copy_map[y][x] == '1' || copy_map[y][x] == 'E' ||
		copy_map[y][x] == 'V')
		return (0);
	if (copy_map[y][x] == 'C')
		found = 1;
	copy_map[y][x] = 'V';
	found += flood_fill_items(copy_map, map, (t_coords){x + 1, y});
	found += flood_fill_items(copy_map, map, (t_coords){x - 1, y});
	found += flood_fill_items(copy_map, map, (t_coords){x, y + 1});
	found += flood_fill_items(copy_map, map, (t_coords){x, y - 1});
	return (found);
}

char **allocate_memory(t_map *map)
{
	char **new_map;
	int i;

	i = 0;
	new_map = malloc(sizeof(char *) * map->rows);
	if (!new_map)
		return NULL;
	while (i < map->rows)
	{
		new_map[i] = malloc(sizeof(char) * (map->cols + 1));
		if (!new_map[i])
		{
			while (i > 0)
				free(new_map[--i]);
			free(new_map);
			return (NULL);
		}
		i++;
	}
	return(new_map);
}

char **copy_map(t_map *map)
{
	char **new_map;
	int i;
	int j;

	i = 0;
	new_map = allocate_memory(map);
	if (!new_map)
		return NULL;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			new_map[i][j] = map->map_data[i][j];
			j++;
		}
		new_map[i][map->cols] = '\0';
		i++;
	}
	return (new_map);
}

void	check_valid_player_position(t_map *map)
{
	char **copied_map;
	int collected;
	int exit_reached;
	int i;

	i = 0;
	copied_map = copy_map(map);
	if (!copied_map)
		exit (1);
	collected = flood_fill_items(copied_map, map, map->player);
	while (i < map->rows)
		free(copied_map[i++]);
	free(copied_map);
	if (collected != map->collectibles)
	{
		ft_putstr_fd("Error\nCan't collect all worms.\n", 2);
		safe_exit(map);
		exit(1);
	}
	i = 0;
	copied_map = copy_map(map);
	if (!copied_map)
		exit (1);
	exit_reached = flood_fill_exit(copied_map, map, map->player, map->exit);
	while (i < map->rows)
		free(copied_map[i++]);
	free(copied_map);
	if (!exit_reached)
	{
		ft_putstr_fd("Error\nPath to the exit is not valid.\n", 2);
		safe_exit(map);
		exit(1);
	}
}
