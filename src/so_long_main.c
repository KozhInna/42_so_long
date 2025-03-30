/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:51:03 by ikozhina          #+#    #+#             */
/*   Updated: 2025/03/30 23:51:11 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#define BPP sizeof(int32_t)

int main(int argc, char **argv)
{
	validate_argv(argc, argv);
	validate_map(argv[1]);
	// if validate map return not 1

// MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
	{
		fprintf(stderr, "%s", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
// // Try to load the file
// 	mlx_texture_t* texture = mlx_load_png("./temp/water.png");
// 	if (!texture)
// 		exit(EXIT_FAILURE);
	
// 	// Convert texture to a displayable image
// 	mlx_image_t* img = mlx_texture_to_image(mlx, texture);
// 	if (!img)
//         exit(EXIT_FAILURE);

// 	// Display the image
// 	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
//         exit(EXIT_FAILURE);

// 	mlx_loop(mlx);

// 	mlx_delete_image(mlx, img);
// 	mlx_delete_texture(texture);

//         // Optional, terminate will clean up any leftover images (not textures!)
// 	mlx_terminate(mlx);
	
	// /* Do stuff */

	// Create and display the image.
	// allocate memory for this image
	mlx_image_t* img = mlx_new_image(mlx, 734, 748);
	// MLX42 to use OpenGL to draw the texture created by mlx_new_image() onto the window’s framebuffer
	// if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	// {
	// 	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	// 	exit(EXIT_FAILURE);
	// }
	
    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    ft_memset(img->pixels, 100, img->width * img->height * BPP);

    mlx_image_to_window(mlx, img, 0, 0);
	printf("coordinates %d - %d\n", img->instances[0].x, img->instances[0].y);
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	// mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
