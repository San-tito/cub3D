/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/25 15:31:32 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	rendering_setup(t_core core)
{
	mlx_set_setting(MLX_MAXIMIZED, 1);
	core.mlx = mlx_init(WIDTH, HEIGHT, PROGRAM, 1);
	if (core.mlx == 0)
		libx_error("mlx error");
	core.img = mlx_new_image(core.mlx, WIDTH, HEIGHT);
	if (core.img == 0 || (mlx_image_to_window(core.mlx, core.img, 0, 0) < 0))
		libx_error("mlx error");
	core.scene.assets.wolf = mlx_load_png(PT_WOLF);
	if (!core.scene.assets.wolf)
		libx_error("mlx error");
	core.img = mlx_texture_to_image(core.mlx, core.scene.assets.wolf);
	if (!core.img)
		libx_error("mlx error");
	if (mlx_image_to_window(core.mlx, core.img, 0, 0) < 0)
		libx_error("mlx error");
	mlx_loop_hook(core.mlx, ft_hook, core.mlx);
	mlx_loop(core.mlx);
}
