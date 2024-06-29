/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:47:13 by droied            #+#    #+#             */
/*   Updated: 2024/06/29 17:32:30 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_hook(void *param)
{
	t_core *core;

	core = (t_core *)param;
	if (mlx_is_key_down(core->mlx, MLX_KEY_ESCAPE))
		terminate(*core);
	else if (mlx_is_key_down(core->mlx, MLX_KEY_UP))
		printf("UP\n");
	else if (mlx_is_key_down(core->mlx, MLX_KEY_DOWN))
		printf("DOWN\n");
	else if (mlx_is_key_down(core->mlx, MLX_KEY_LEFT))
	{
		mlx_delete_image(core->mlx, core->img);
		core->scene.minimap.p.a -= 0.1;
		if (core->scene.minimap.p.a < 0)
			core->scene.minimap.p.a += 2 * PI;
		draw_minimap(*core);
	}
	else if (mlx_is_key_down(core->mlx, MLX_KEY_RIGHT))
	{
		mlx_delete_image(core->mlx, core->img);
		core->scene.minimap.p.a += 0.1;
		if (core->scene.minimap.p.a > 2 * PI)
			core->scene.minimap.p.a -= 2 * PI;
		draw_minimap(*core);
	}
}
