/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:32:19 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/03 23:25:16 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	safe_exit(t_map *map)
{
	int i;

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
	map = NULL;
}

void	is_ractangular(t_map *map)
{
	int i;

	map->cols = ft_strlen(map->map_data[0]);
	i = 1;
	while (i < map->rows)
	{
		if (map->cols != (int)ft_strlen(map->map_data[i++]))
		{
			ft_putstr_fd("Error\nMap must be rectangular\n", 2);
			safe_exit(map);
			exit(1);
		}
	}
	if (map->rows == map->cols)
	{
		ft_putstr_fd("Error\nMap must be rectangular\n", 2);
		safe_exit(map);
		exit(1);
	}
}
void	check_walls(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->map_data[i][j])
		{
			if ((i == 0 || i == map->rows - 1) && map->map_data[i][j] != '1')
			{
				ft_putstr_fd("Error\nMap must be surrounded by walls\n", 2);
				safe_exit(map);
				exit(1);
			}
			if ((j == 0 || j == map->cols - 1) && map->map_data[i][j] != '1')
			{
				ft_putstr_fd("Error\nMap must be surrounded by walls\n", 2);
				safe_exit(map);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	check_valid_components(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->map_data[i][j])
		{
			if (map->map_data[i][j] == 'P')
			{
				map->pl_x = j;
				map->pl_y = i;
			}
			if (map->map_data[i][j] == 'E')
			{
				map->ex_x = j;
				map->ex_y = i;
			}
			if (!ft_strchr("01CEP", map->map_data[i][j]))
			{
				ft_putstr_fd("Error\nMap must be composed of only these characters: 0, 1, C, E, P\n", 2);
				safe_exit(map);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	count_collectibles(t_map *map)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (i < map->rows)
	{
		j = 0;
		while (map->map_data[i][j])
		{
			if (map->map_data[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	map->collectibles = count;
}
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
	{
		ft_putstr_fd("Error\nMap must contain exactly 1 exit, 1 player and at least 1 collectible\n", 2);
		safe_exit(map);
		exit(1);
	}
}

int		flood_fill_exit(t_map *map, int x, int y, int x2, int y2)
{
	char temp;
	int found;
	
	if (x == x2 && y == y2)
		return (1);	
	if (x < 0 || y < 0 || y >= map->rows || x >= map->cols || 
		map->map_data[y][x] == '1' || map->map_data[y][x] == 'V')
		return (0);
	temp = map->map_data[y][x];
	map->map_data[y][x] = 'V';
	found = (flood_fill_exit(map, x + 1, y, x2, y2) || 
			flood_fill_exit(map, x - 1, y, x2, y2) ||
			flood_fill_exit(map, x, y + 1, x2, y2) || 
			flood_fill_exit(map, x, y - 1, x2, y2));
	map->map_data[y][x] = temp;
	return (found);
}
int	flood_fill_items(char **copy_map, t_map *map, int x, int y)
{
	int found;
	
	found = 0;
	if (x < 0 || x >= map->cols || y < 0 || y >= map->rows ||
		copy_map[y][x] == '1' || copy_map[y][x] == 'E' ||
		copy_map[y][x] == 'V')
		return (0);
	if (copy_map[y][x] == 'C')
		found = 1;
	copy_map[y][x] = 'V';
	found += flood_fill_items(copy_map, map, x + 1, y);
	found += flood_fill_items(copy_map, map, x - 1, y);
	found += flood_fill_items(copy_map, map, x, y + 1);
	found += flood_fill_items(copy_map, map, x, y - 1);
	return (found);
}

char **copy_map(t_map *map)
{
	char **new_map;
	int i;
	int j;
	
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

void	check_valid_position(t_map *map)
{
	char **copied_map;
	int collected;
	int i;

	i = 0;
	copied_map = copy_map(map);
	if (!copied_map)
		exit (1);
	collected = flood_fill_items(copied_map, map, map->pl_x, map->pl_y);
	while (i < map->rows)
		free(copied_map[i++]);
	free(copied_map);
	if (collected != map->collectibles)
	{
		ft_putstr_fd("Error\nCan't collect all worms.\n", 2);
		safe_exit(map);
		exit(1);
	}
	printf("collected - %d\n", collected);
	if (!flood_fill_exit(map, map->pl_x, map->pl_y, map->ex_x, map->ex_y))
	{
		ft_putstr_fd("Error\nPath to the exit is not valid.\n", 2);
		safe_exit(map);
		exit(1);
	}
	printf("path is valid\n");	

}

t_map	*validate_map(char *map_file)
{
	t_map *map;

	map = parse_map(map_file);
	if (!map)
	{
		safe_exit(map);
		exit(1);
	}
	is_ractangular(map);
	check_walls(map);
	check_valid_components(map);
	count_collectibles(map);
	map->width = map->cols * TILE_SIZE;
	map->height = map->rows * TILE_SIZE;
	check_duplicates(map);
	check_valid_position(map);
	// free all
	// safe_exit(map);
	return (map);
}
