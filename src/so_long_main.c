/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:51:03 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/21 15:07:20 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_extention(char *file_name)
{
	char *pnt_dot;
	int is_equal;

	pnt_dot = ft_strrchr(file_name, '.');
	if (pnt_dot == NULL)
	{
		printf("No extention\n");
		return ;
	}
	is_equal = ft_strcmp(pnt_dot, ".ber");
	if (!is_equal)
		printf("Equal\n");
	else
		printf("Not Equal\n");
}



int main(int argc, char **argv)
{
	if (argc == 2)
		printf("%s - ", argv[1]);
	check_extention(argv[1]);
}
