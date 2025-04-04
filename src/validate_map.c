/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:32:19 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/04 14:52:43 by ikozhina         ###   ########.fr       */
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
				map->player.x = j;
				map->player.y = i;
			}
			if (map->map_data[i][j] == 'E')
			{
				map->exit.x = j;
				map->exit.y = i;
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
	check_duplicates(map);
	check_valid_player_position(map);
	return (map);
}
