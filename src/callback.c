/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:47:13 by droied            #+#    #+#             */
/*   Updated: 2024/09/12 16:40:19 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move(t_scene *scene, float factor, int32_t key)
{
	if (key == 0)
	{
		if (scene->map.cells[(int)(scene->player.pos.y)][(int)(scene->player.pos.x
				+ scene->player.plane.x)] == SPACE)
		{
			scene->player.pos.x += scene->player.plane.x * factor;
			scene->refresh = 1;
		}
	}
	else
	{
		if (scene->map.cells[(int)(scene->player.pos.y
				+ scene->player.dir.y)][(int)(scene->player.pos.x)] == SPACE)
		{
			scene->player.pos.y += scene->player.dir.y * factor;
			scene->refresh = 1;
		}
	}
}

void	event_listener(mlx_t *mlx, t_scene *scene)
{
	const float	move_speed = 1;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		move(scene, move_speed, 1);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		move(scene, -move_speed, 1);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		move(scene, -move_speed, 0);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		move(scene, move_speed, 0);
}
