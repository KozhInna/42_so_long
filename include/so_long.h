/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:49:20 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/25 10:22:57 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include <fcntl.h>

/*delete lib below*/
#include <stdio.h>

typedef struct s_map
{
	char **map_data;
	size_t rows;
	size_t columns;
} t_map;

void	validate_argv(int argc, char **argv);
void	validate_map(char *map_file);

#endif
