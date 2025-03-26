/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:51:03 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/26 12:54:31 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int main(int argc, char **argv)
{
	validate_argv(argc, argv);
	validate_map(argv[1]);
	// if validate map return not 1

	return (0);
}
