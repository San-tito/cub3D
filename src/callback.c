/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:47:13 by droied            #+#    #+#             */
/*   Updated: 2024/09/20 16:50:58 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	move(t_scene *scene, float fx, float fy, double move_speed)
{
	if (scene->map.cells[(int)(scene->player.pos.y + fy
			* move_speed)][(int)(scene->player.pos.x)] == SPACE)
		scene->player.pos.y += fy * move_speed;
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
	scene->player.a += angle;
	if (angle < 0)
		scene->player.a -= 2 * PI;
	else
		scene->player.a += 2 * PI;
	scene->refresh = 1;
}

void	mouse_listener(mlx_t *mlx, t_scene *scene)
{
	static float	last = 0;
	float			delta;
	t_ivec			pos;

	(void)scene;
	mlx_get_mouse_pos(mlx, &pos.x, &pos.y);
	delta = (pos.x - last);
	if (last != pos.x)
		rotate(scene, delta * SENSITIVITY);
	last = pos.x;
}

void	event_listener(mlx_t *mlx, t_scene *scene)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
		move(scene, scene->player.dir.x, scene->player.dir.y, SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
		move(scene, -scene->player.dir.x, -scene->player.dir.y, SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move(scene, scene->player.dir.y, -scene->player.dir.x, SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move(scene, -scene->player.dir.y, scene->player.dir.x, SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate(scene, -SENSITIVITY * 42);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate(scene, SENSITIVITY * 42);
}
