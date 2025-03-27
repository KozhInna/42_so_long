/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:32:19 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/27 10:37:32 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	safe_exit(t_map *map)
{
	size_t i;

	i = 0;
	if (!map)
		exit(1);
	while (i < map->rows)
		free(map->map_data[i++]);
	free(map->map_data);
	free(map);
	exit(1);
}

void	is_ractangular(t_map *map)
{
	size_t i;

	map->columns = ft_strlen(map->map_data[0]);
	i = 1;
	while (i < map->rows)
	{
		if (map->columns != ft_strlen(map->map_data[i++]))
		{
			ft_putstr_fd("Error\nMap must be rectangular\n", 2);
			safe_exit(map);
		}
	}
	if (map->rows == map->columns)
	{
		ft_putstr_fd("Error\nMap must be rectangular\n", 2);
		safe_exit(map);
	}
}
void	check_walls(t_map *map)
{
	size_t i;
	size_t j;

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
			}
			if ((j == 0 || j == map->columns - 1) && map->map_data[i][j] != '1')
			{
				ft_putstr_fd("Error\nMap must be surrounded by walls\n", 2);
				safe_exit(map);
			}
			j++;
		}
		i++;
	}
}


int	validate_map(char *map_file)
{
	t_map *map;

	map = parse_map(map_file);
	if (!map)
		safe_exit(map);
	is_ractangular(map);
	check_walls(map);
	printf("valid map\n");
	return (1);
}