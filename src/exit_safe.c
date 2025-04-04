/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_safe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:48:49 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/05 11:28:20 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"so_long.h"

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
void error_exit(char *message, t_map *map)
{
	ft_putstr_fd(message, 2);
	safe_exit(map);
	exit(1);
}