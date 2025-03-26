/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:32:19 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/26 22:49:54 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_ractangular(t_map *map)
{
	size_t i;

	map->columns = ft_strlen(map->map_data[0]);
	i = 1;
	while (i < map->rows)
	{
		if (map->columns != ft_strlen(map->map_data[i++]))
			return (1);
	}
	if (map->rows == map->columns)
		return (1);
	return (0);
}

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

int	validate_map(char *map_file)
{
	t_map *map;

	map = parse_map(map_file);
	if (!map)
		safe_exit(map);
	if (is_ractangular(map) != 0)
	{
		ft_putstr_fd("Error\nMap must be rectangular\n", 2);
		safe_exit(map);
	}
	return (1);
}