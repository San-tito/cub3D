/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:47:13 by droied            #+#    #+#             */
/*   Updated: 2024/06/26 00:47:39 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
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
