/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:49:20 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/27 15:22:31 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "../MLX42/include/MLX42/MLX42.h"
#define WIDTH 800
#define HEIGHT 600
# include "libft.h"
# include <fcntl.h>

/*delete lib below*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_map
{
	char **map_data;
	size_t rows;
	size_t columns;
} t_map;

void	validate_argv(int argc, char **argv);
int	validate_map(char *map_file);
t_map	*parse_map(char *map_file);

#endif
