/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:56:51 by deordone          #+#    #+#             */
/*   Updated: 2024/09/13 16:06:25 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "print.h"
#include "raycast.h"

static void	init_ray(t_ray *ray, t_player player, float camera)
{
	ray->dir.x = player.dir.x + player.plane.x * camera;
	ray->dir.y = player.dir.y + player.plane.y * camera;
	ray->pos.x = (int)player.pos.x;
	ray->pos.y = (int)player.pos.y;
	ray->deltadist.x = (ray->dir.x == 0) ? 1e30 : fabs(1 / ray->dir.x);
	ray->deltadist.y = (ray->dir.y == 0) ? 1e30 : fabs(1 / ray->dir.y);
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (player.pos.x - ray->pos.x) * ray->deltadist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = (ray->pos.x + 1.0 - player.pos.x) * ray->deltadist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (player.pos.y - ray->pos.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y = (ray->pos.y + 1.0 - player.pos.y) * ray->deltadist.y;
	}
}

static void	perform_dda(t_ray *ray, t_cell **cells)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->pos.y += ray->step.y;
			ray->side = 1;
		}
		if (cells[(int)ray->pos.y][(int)ray->pos.x] > SPACE)
			hit++;
	}
}

void	calculate_wall(t_wall *wall, t_ray *ray, int height)
{
	if (ray->side == 0)
		wall->dist = (ray->sidedist.x - ray->deltadist.x);
	else
		wall->dist = (ray->sidedist.y - ray->deltadist.y);
	wall->height = (int)(height / wall->dist);
	wall->start = -wall->height / 2 + height / 2;
	if (wall->start < 0)
		wall->start = 0;
	wall->end = wall->height / 2 + height / 2;
	if (wall->end >= height)
		wall->end = height - 1;
	wall->color = 65280;
	if (ray->side == 1)
		wall->color = wall->color / 2;
}

static void	draw_wall(mlx_image_t *image, unsigned int x, t_wall wall)
{
	if (wall.end < wall.start)
	{
		wall.start += wall.end;
		wall.end = wall.start - wall.end;
		wall.start -= wall.end;
	}
	if (wall.end < 0 || (unsigned)wall.start >= image->height
		|| x >= image->width)
		return ;
	if (wall.start < 0)
		wall.start = 0;
	if ((unsigned)wall.end >= image->width)
		wall.end = image->height - 1;
	while (wall.start <= wall.end)
		put_pixel(image, x, wall.start++, wall.color);
}

void	raycast(mlx_image_t *image, t_scene scene)
{
	unsigned int	x;
	t_ray			ray;
	t_wall			wall;

	x = 0;
	while (x < image->width)
	{
		init_ray(&ray, scene.player, 2 * x / (float)image->width - 1);
		perform_dda(&ray, scene.map.cells);
		calculate_wall(&wall, &ray, image->height);
		draw_wall(image, x, wall);
		x++;
	}
}
