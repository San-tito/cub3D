/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:56:51 by deordone          #+#    #+#             */
/*   Updated: 2024/09/20 11:07:21 by santito          ###   ########.fr       */
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

void	calculate_wall(t_wall *wall, t_ray *ray, int height,
		t_textures textures)
{
	if (ray->side == 0)
		wall->dist = (ray->sidedist.x - ray->deltadist.x);
	else
		wall->dist = (ray->sidedist.y - ray->deltadist.y);
	wall->height = (int)(height / wall->dist);
	wall->start = (-wall->height >> 1) + (height >> 1);
	if (wall->start < 0)
		wall->start = 0;
	wall->end = (wall->height >> 1) + (height >> 1);
	if (wall->end >= height)
		wall->end = height - 1;
	wall->texture = textures.west;
	if (ray->side == 0)
		wall->hit = ray->pos.y + wall->dist * ray->dir.y;
	else
		wall->hit = ray->pos.x + wall->dist * ray->dir.x;
	wall->hit -= floor((wall->hit));
	wall->tex.y = (int)(wall->hit * wall->texture->width);
	if (ray->side == 0 && ray->dir.x > 0)
		wall->tex.y = wall->texture->width - wall->tex.y - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		wall->tex.y = wall->texture->width - wall->tex.y - 1;
}

static void	draw_wall(mlx_image_t *image, unsigned int x, t_wall wall)
{
	int	color;

	if (wall.end < wall.start)
	{
		wall.start += wall.end;
		wall.end = wall.start - wall.end;
		wall.start -= wall.end;
	}
	if (wall.end < 0 || (unsigned)wall.start >= image->height
		|| x >= image->width)
		return ;
	wall.step = 1.0 * wall.texture->height / wall.height;
	wall.tex_pos = (wall.start - image->height / 2 + wall.height / 2)
		* wall.step;
	while (wall.start <= wall.end)
	{
		wall.tex.y = (int)wall.tex_pos & (wall.texture->height - 1);
		wall.tex_pos += wall.step;
		color = wall.texture->pixels[wall.texture->height * wall.tex.y
			+ wall.tex.x];
		put_pixel(image, x, wall.start++, color);
	}
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
		calculate_wall(&wall, &ray, image->height, scene.textures);
		draw_wall(image, x, wall);
		x++;
	}
}
