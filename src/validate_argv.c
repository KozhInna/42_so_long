/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:27:41 by ikozhina          #+#    #+#             */
/*   Updated: 2025/04/05 12:58:49 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void check_argv_count(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Error\nUsage: %s (one argument must be specified)\n", argv[0]);
		exit(1);
	}
	if (!argv[1] || argv[1][0] == '\0')
	{
		ft_printf("Error\nUsage: %s (map file with .ber extension must be specified)\n", argv[0]);
		exit(1);
	}
}

static void	check_file_extension(char **argv)
{
	char *dot_ptr;

	dot_ptr = ft_strrchr(argv[1], '.');
	if (!dot_ptr || ft_strcmp(dot_ptr, ".ber") != 0)
	{
		ft_printf("Error\nUsage: ./so_long %s (map must have .ber extension)\n", argv[1]);
		exit(1);
	}
	if (ft_strcmp(argv[1], ".ber") == 0)
	{
		ft_printf("Error\nUsage: ./so_long %s (map can't be a hidden file)\n", argv[1]);
		exit(1);
	}
}

void validate_argv(int argc, char **argv)
{
	check_argv_count(argc, argv);
	check_file_extension(argv);
}
