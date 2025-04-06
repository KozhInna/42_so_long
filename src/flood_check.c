/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:41:02 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/06 10:48:49 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		flood_fill_exit(char **copy_map, t_map *map, t_coords player)
{
	int found;
	int x;
	int y;
	int x2;
	int y2;

	x = player.x;
	y = player.y;
	x2 = map->exit.x;
	y2 = map->exit.y;
	if (x == x2 && y == y2)
		return (1);
	if (x < 0 || y < 0 || y >= map->rows || x >= map->cols
		|| copy_map[y][x] == '1' || copy_map[y][x] == 'V')
		return (0);
	copy_map[y][x] = 'V';
	found = (flood_fill_exit(copy_map, map, (t_coords){x + 1, y})
			|| flood_fill_exit(copy_map, map, (t_coords){x - 1, y})
			|| flood_fill_exit(copy_map, map, (t_coords){x, y + 1})
			|| flood_fill_exit(copy_map, map, (t_coords){x, y - 1}));
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
	if (x < 0 || x >= map->cols || y < 0 || y >= map->rows
		|| copy_map[y][x] == '1' || copy_map[y][x] == 'E'
		|| copy_map[y][x] == 'V')
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

int	flood_check(t_map *map, int (*func)(char **, t_map *, t_coords))
{
	int i;
	int result;
	char **copied_map;

	i = 0;
	copied_map = copy_map(map);
	if (!copied_map)
		exit (1);
	result = func(copied_map, map, map->player);
	while (i < map->rows)
		free(copied_map[i++]);
	free(copied_map);
	return (result);
}
