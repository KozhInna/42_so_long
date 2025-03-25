/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:32:19 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/25 11:44:59 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void initialise_struct(t_map **map, size_t rows)
{
	(*map) = malloc(sizeof(t_map));
	if (!(*map))
		return ;
	(*map)->rows = rows;
	(*map)->columns = 0;
	(*map)->map_data = malloc(sizeof(char *) * rows);
	if (!(*map)->map_data)
	{
		free(*map);
		(*map) = NULL;
		return ;
	}
}

size_t count_rows(int fd)
{
	char	*line_read;
	size_t rows_count;

	line_read = NULL;
	rows_count = 0;
	while (1)
	{
		line_read = get_next_line(fd);
		if (line_read == NULL)
			break ;
		if (line_read != NULL)
		{
			rows_count++;
			free(line_read);
		}
	}
	return (rows_count);
}
void	validate_map(char *map_file)
{
	int		fd;
	size_t rows;
	t_map *map;

	map = NULL;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit (1);
	rows = count_rows(fd);
	close(fd);
	initialise_struct(&map, rows);
	if (!map)
		return ;
	printf("number of lines - %ld\n", rows);
}
