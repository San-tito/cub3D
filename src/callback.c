/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:47:13 by droied            #+#    #+#             */
/*   Updated: 2024/06/26 02:27:06 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_hook(void *param)
{
	t_core	core;

	core = *(t_core *)param;
	if (mlx_is_key_down(core.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(core.mlx);
	if (mlx_is_key_down(core.mlx, MLX_KEY_UP))
		printf("UP\n");
	if (mlx_is_key_down(core.mlx, MLX_KEY_DOWN))
		printf("DOWN\n");
	if (mlx_is_key_down(core.mlx, MLX_KEY_LEFT))
	{
		core.scene.minimap.p.a -= 0.1;
		draw_character(core, core.scene.minimap.p, MINI_P_SIZE);
	}
	if (mlx_is_key_down(core.mlx, MLX_KEY_RIGHT))
	{
		core.scene.minimap.p.a += 0.1;
		draw_character(core, core.scene.minimap.p, MINI_P_SIZE);
	}
}
