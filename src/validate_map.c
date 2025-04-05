/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:32:19 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/05 11:29:14 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	is_ractangular(t_map *map)
{
	int i;

	map->cols = ft_strlen(map->map_data[0]);
	i = 1;
	while (i < map->rows)
	{
		if (map->cols != (int)ft_strlen(map->map_data[i++]))
			error_exit("Error\nMap must be rectangular\n", map);
	}
	if (map->rows == map->cols)
		error_exit("Error\nMap must be rectangular\n", map);
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
				error_exit("Error\nMap must be surrounded by walls\n", map);
			if ((j == 0 || j == map->cols - 1) && map->map_data[i][j] != '1')
				error_exit("Error\nMap must be surrounded by walls\n", map);
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
				map->player.x = j;
				map->player.y = i;
			}
			if (map->map_data[i][j] == 'E')
			{
				map->exit.x = j;
				map->exit.y = i;
			}
			if (!ft_strchr("01CEP", map->map_data[i][j]))
				error_exit("Error\nMap must be composed of only these characters: 0, 1, C, E, P\n", map);
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
	map->width = map->cols * T_SIZE;
	map->height = map->rows * T_SIZE;
	check_valid_player_position(map);
	return (map);
}
