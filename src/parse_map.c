/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:18:34 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/31 13:47:56 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialise_struct(t_map **map, int rows)
{
	int	i;

	i = 0;
	(*map) = malloc(sizeof(t_map));
	if (!(*map))
		return ;
	(*map)->rows = rows;
	(*map)->cols = 0;
	(*map)->pl_x = 0;
	(*map)->pl_y = 0;
	(*map)->map_data = malloc(sizeof(char *) * rows);
	if (!(*map)->map_data)
	{
		free(*map);
		(*map) = NULL;
		return ;
	}
	while (i < rows)
		(*map)->map_data[i++] = NULL;
}

int	count_rows(int fd)
{
	char	*line_read;
	int	rows_count;

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

int	store_map_line(char *line_read, t_map *map, int i)
{
	char	*newline_ptr;

	if (!line_read)
		return (1);
	newline_ptr = ft_strchr(line_read, '\n');
	if (newline_ptr != NULL)
		*newline_ptr = '\0';
	map->map_data[i] = ft_strdup(line_read);
	free(line_read);
	if (!map->map_data[i])
	{
		while (i > 0)
			free(map->map_data[--i]);
		free(map->map_data);
		free(map);
		return (1);
	}
	return (0);
}

void	read_and_store_map_lines(int fd, t_map *map)
{
	char	*line_read;
	int	i;

	line_read = NULL;
	i = 0;
	while (i < map->rows)
	{
		line_read = get_next_line(fd);
		if (line_read == NULL)
			break ;
		if (store_map_line(line_read, map, i) != 0)
			exit(1);
		i++;
	}
	printf("from parse func 2 row - \n%s\n", map->map_data[1]);
}

t_map	*parse_map(char *map_file)
{
	int		fd;
	int	rows;
	t_map	*map;

	map = NULL;
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	rows = count_rows(fd);
	close(fd);
	initialise_struct(&map, rows);
	if (!map)
		return (NULL);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	read_and_store_map_lines(fd, map);
	close(fd);
	// printf("from validate map 2 row - \n%s\n", map->map_data[1]);
	// printf("number of lines - %ld\n", rows);
	return(map);
}
