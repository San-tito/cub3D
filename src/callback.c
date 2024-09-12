/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:47:13 by droied            #+#    #+#             */
/*   Updated: 2024/09/12 21:25:08 by santito          ###   ########.fr       */
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
	const double move_speed = 0.2;
	const double rot_speed = 0.2;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		if(scene->map.cells[(int)(scene->player.pos.x + scene->player.dir.x * move_speed)][(int)(scene->player.pos.y)] == SPACE) scene->player.pos.x += scene->player.dir.x * move_speed;
      if(scene->map.cells[(int)(scene->player.pos.x)][(int)(scene->player.pos.y + scene->player.dir.y * move_speed)] ==
 SPACE) scene->player.pos.y += scene->player.dir.y * move_speed;
		scene->refresh = 1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
	if(scene->map.cells[(int)(scene->player.pos.x - scene->player.dir.x * move_speed)][(int)(scene->player.pos.y)] == SPACE) scene->player.pos.x -= scene->player.dir.x * move_speed;
      if(scene->map.cells[(int)(scene->player.pos.x)][(int)(scene->player.pos.y - scene->player.dir.y * move_speed)] ==
 SPACE) scene->player.pos.y -= scene->player.dir.y * move_speed;
		scene->refresh = 1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		    double oldDirX = scene->player.dir.x;
      scene->player.dir.x = scene->player.dir.x * cos(rot_speed) - scene->player.dir.y * sin(rot_speed);
      scene->player.dir.y = oldDirX * sin(rot_speed) + scene->player.dir.y * cos(rot_speed);
      double oldPlaneX = scene->player.plane.x;
      scene->player.plane.x = scene->player.plane.x * cos(rot_speed) - scene->player.plane.y * sin(rot_speed);
      scene->player.plane.y = oldPlaneX * sin(rot_speed) + scene->player.plane.y * cos(rot_speed);
		scene->refresh = 1;

	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		    double oldDirX = scene->player.dir.x;
      scene->player.dir.x = scene->player.dir.x * cos(-rot_speed) - scene->player.dir.y * sin(-rot_speed);
      scene->player.dir.y = oldDirX * sin(-rot_speed) + scene->player.dir.y * cos(-rot_speed);
      double oldPlaneX = scene->player.plane.x;
      scene->player.plane.x = scene->player.plane.x * cos(-rot_speed) - scene->player.plane.y * sin(-rot_speed);
      scene->player.plane.y = oldPlaneX * sin(-rot_speed) + scene->player.plane.y * cos(-rot_speed);
		scene->refresh = 1;
	}
}
