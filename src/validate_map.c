/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:32:19 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/24 14:59:16 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t count_lines(int fd)
{
	char	*line_read;
	size_t lines_count;

	line_read = " ";
	lines_count = 0;
	while (line_read != NULL)
	{
		line_read = get_next_line(fd);
		if (line_read != NULL)
			lines_count++;
	}
	return (lines_count);
}
void	validate_map(char *map_file)
{
	int		fd;
	size_t lines_count;
	// t_map map;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit (1);
	lines_count = count_lines(fd);
	printf("number of lines - %ld\n", lines_count);
}
