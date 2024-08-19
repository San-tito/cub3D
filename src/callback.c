/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:47:13 by droied            #+#    #+#             */
/*   Updated: 2024/08/19 11:18:36 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	event_listener(mlx_t *mlx, t_scene *scene)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		scene->refresh = 1;
		scene->player.p.x += scene->player.p.dx;
		scene->player.p.y += scene->player.p.dy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		scene->refresh = 1;
		scene->player.p.x -= scene->player.p.dx;
		scene->player.p.y -= scene->player.p.dy;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		scene->refresh = 1;
		scene->player.p.a -= 0.1;
		if (scene->player.p.a < 0)
			scene->player.p.a += 2 * PI;
		scene->player.p.dx = cos(scene->player.p.a) * 5; 
		scene->player.p.dy = sin(scene->player.p.a) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		scene->refresh = 1;
		scene->player.p.a += 0.1;
		if (scene->player.p.a > 2 * PI)
			scene->player.p.a -= 2 * PI;
		scene->player.p.dx = cos(scene->player.p.a) * 5; 
		scene->player.p.dy = sin(scene->player.p.a) * 5;
	}
}
