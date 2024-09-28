/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 00:47:13 by droied            #+#    #+#             */
/*   Updated: 2024/09/28 15:23:14 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_collision(t_cell cell)
{
	return (cell == SPACE || cell == DOOR_OPEN);
}

static void	move(t_scene *scene, float fx, float fy, double move_speed)
{
	if (check_collision(scene->map.cells[(int)(scene->player.pos.y + fy
				* (move_speed + 0.01))][(int)(scene->player.pos.x)]))
		scene->player.pos.y += fy * move_speed;
	if (check_collision(scene->map.cells[(int)(scene->player.pos.y)][(int)(scene->player.pos.x
				+ fx * (move_speed + 0.01))]))
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

static void	interact(t_scene *scene)
{
	/* Animate... */
	interact_with_door(&scene->map, scene->player.pos, scene->player.dir);
}

void	mouse_listener(mlx_t *mlx, t_scene *scene)
{
	static float	last = 0;
	float			delta;
	t_ivec			pos;

	mlx_get_mouse_pos(mlx, &pos.x, &pos.y);
	delta = (pos.x - last);
	if (last != 0)
		rotate(scene, delta * SENSITIVITY);
	last = pos.x;
}

void	event_listener(mlx_t *mlx, t_scene *scene)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_SPACE) || mlx_is_mouse_down(mlx,
			MLX_MOUSE_BUTTON_LEFT))
		interact(scene);
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
