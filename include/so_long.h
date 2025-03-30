/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:49:20 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/30 23:53:54 by ikozhina         ###   ########.fr       */
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
	int rows;
	int cols;
	int exit;
	int collectibles;
} t_map;

typedef struct game
{
	mlx_t *mlx;
	t_map *map;
	int width;
	int height;
	mlx_image_t *img_player;
	mlx_image_t *img_exit;
	mlx_image_t *img_collectible;
	mlx_image_t *img_wall;
	mlx_image_t *img_floor;
} t_game;

void	validate_argv(int argc, char **argv);
int		validate_map(char *map_file);
t_map	*parse_map(char *map_file);

#endif
