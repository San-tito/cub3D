/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:47:13 by droied            #+#    #+#             */
/*   Updated: 2024/09/13 16:51:04 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move(t_scene *scene, float fx, float fy, double move_speed)
{
	// Move along Y-axis if no wall is blocking the movement
	if (scene->map.cells[(int)(scene->player.pos.y + fy
			* move_speed)][(int)(scene->player.pos.x)] == SPACE)
		scene->player.pos.y += fy * move_speed;
	// Move along X-axis if no wall is blocking the movement
	if (scene->map.cells[(int)(scene->player.pos.y)][(int)(scene->player.pos.x
			+ fx * move_speed)] == SPACE)
		scene->player.pos.x += fx * move_speed;
	scene->refresh = 1;
}

void	rotate(t_scene *scene, double angle)
{
	float	dir;
	float	plane;

	dir = scene->player.dir.x;
	scene->player.dir.x = scene->player.dir.x * cos(angle) - scene->player.dir.y
		* sin(angle);
	scene->player.dir.y = dir * sin(angle) + scene->player.dir.y * cos(angle);
	plane = scene->player.plane.x;
	scene->player.plane.x = scene->player.plane.x * cos(angle)
		- scene->player.plane.y * sin(angle);
	scene->player.plane.y = plane * sin(angle) + scene->player.plane.y
		* cos(angle);
	scene->refresh = 1;
}

void	mouse_listener(double xpos, double ypos, void *param)
{
	t_core *core;
	core = (t_core *)param;
	static double last_xpos = 0;
	const double	rot_speed = 0.05;

	if (xpos == core->img->width -1 || xpos <= 5)
		mlx_set_mouse_pos(core->mlx, core->img->width / 2, ypos);
	if (xpos > last_xpos)
		rotate(&core->scene, rot_speed);
	if (xpos < last_xpos)
		rotate(&core->scene, -rot_speed);
	last_xpos = xpos;
}

void	event_listener(mlx_t *mlx, t_scene *scene)
{
	const double	move_speed = 0.1;
	const double	rot_speed = 0.05;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
		move(scene, scene->player.dir.x, scene->player.dir.y, move_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
		move(scene, -scene->player.dir.x, -scene->player.dir.y, move_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move(scene, scene->player.dir.y, -scene->player.dir.x, move_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move(scene, -scene->player.dir.y, scene->player.dir.x, move_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate(scene, -rot_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate(scene, rot_speed);
}
