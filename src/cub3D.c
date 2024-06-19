/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:11 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/19 20:05:22 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		printf("UP\n");
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		printf("DOWN\n");
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		printf("LEFT\n");
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		printf("RIGHT\n");
}

// -----------------------------------------------------------------------------

int32_t	main(int ac, char **av)
{
	mlx_image_t	*img;
	mlx_t		*mlx;

	check_map(ac, av);
	mlx_set_setting(MLX_MAXIMIZED, 1);
	mlx = mlx_init(WIDTH, HEIGHT, PROGRAM, 1);
	if (mlx == 0)
		ft_error();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (img == 0 || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
