/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/20 00:11:08 by sguzman          ###   ########.fr       */
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

void	rendering_setup(t_game game)
{
	mlx_set_setting(MLX_MAXIMIZED, 1);
	game.mlx = mlx_init(WIDTH, HEIGHT, PROGRAM, 1);
	if (game.mlx == 0)
		libx_error();
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	if (game.img == 0 || (mlx_image_to_window(game.mlx, game.img, 0, 0) < 0))
		libx_error();
	mlx_loop_hook(game.mlx, ft_hook, game.mlx);
	mlx_loop(game.mlx);
}
