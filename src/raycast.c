/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:56:51 by deordone          #+#    #+#             */
/*   Updated: 2024/09/28 18:38:21 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_ray(t_ray *ray, t_player player, double camera)
{
	ray->dir.x = player.dir.x + player.plane.x * camera;
	ray->dir.y = player.dir.y + player.plane.y * camera;
	ray->pos.x = (int)player.pos.x;
	ray->pos.y = (int)player.pos.y;
	ray->deltadist.x = 1e30;
	if (ray->dir.x != 0)
		ray->deltadist.x = fabs(1 / ray->dir.x);
	ray->deltadist.y = 1e30;
	if (ray->dir.y != 0)
		ray->deltadist.y = fabs(1 / ray->dir.y);
	ray->step.x = (ray->dir.x > 0) + ((ray->dir.x < 0) * -1);
	ray->step.y = (ray->dir.y > 0) + ((ray->dir.y < 0) * -1);
	if (ray->dir.x < 0)
		ray->sidedist.x = (player.pos.x - ray->pos.x) * ray->deltadist.x;
	else
		ray->sidedist.x = (ray->pos.x + 1.0 - player.pos.x) * ray->deltadist.x;
	if (ray->dir.y < 0)
		ray->sidedist.y = (player.pos.y - ray->pos.y) * ray->deltadist.y;
	else
		ray->sidedist.y = (ray->pos.y + 1.0 - player.pos.y) * ray->deltadist.y;
}

static void	perform_dda(t_ray *ray, t_cell **cells)
{
	int		hit;
	t_cell	current;

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
		current = cells[ray->pos.y][ray->pos.x];
		if (current > SPACE && current < DOOR_OPEN)
			hit++;
	}
}

static void	calculate_wall(t_wall *wall, t_ray *ray, unsigned int height)
{
	if (ray->side == 0)
		wall->dist = (ray->sidedist.x - ray->deltadist.x);
	else
		wall->dist = (ray->sidedist.y - ray->deltadist.y);
	wall->height = (int)(height / wall->dist);
	wall->start = (height >> 1) - (wall->height >> 1);
	if (wall->start < 0)
		wall->start = 0;
	wall->end = (wall->height >> 1) + (height >> 1);
	if (wall->end >= (int)height)
		wall->end = height - 1;
}

static void	calculate_tex(t_wall *wall, t_fvec pos, t_ray ray,
		t_textures textures)
{
	double	x;

	if (ray.side == 0 && ray.step.x < 0)
		wall->texture = textures.west;
	else if (ray.side == 0 && ray.step.x > 0)
		wall->texture = textures.east;
	else if (ray.side == 1 && ray.step.y > 0)
		wall->texture = textures.south;
	else if (ray.side == 1 && ray.step.y < 0)
		wall->texture = textures.north;
	if (ray.side == 0)
		x = pos.y + wall->dist * ray.dir.y;
	else
		x = pos.x + wall->dist * ray.dir.x;
	x -= floor(x);
	wall->tex.x = (int)(x * (double)wall->texture->width);
	if (ray.side == 0 && ray.dir.x > 0)
		wall->tex.x = wall->texture->width - wall->tex.x - 1;
	if (ray.side == 1 && ray.dir.y < 0)
		wall->tex.x = wall->texture->width - wall->tex.x - 1;
}

void	raycast(mlx_image_t *image, t_scene scene)
{
	unsigned int	x;
	t_ray			ray;
	t_wall			wall;
	t_cell			state;

	x = 0;
	while (x < image->width)
	{
		init_ray(&ray, scene.player, 2 * x / (double)image->width - 1);
		perform_dda(&ray, scene.map.cells);
		state = scene.map.cells[ray.pos.y][ray.pos.x];
		calculate_wall(&wall, &ray, image->height);
		calculate_tex(&wall, scene.player.pos, ray, scene.textures);
		if (state > WALL && scene.textures.door)
			wall.texture = scene.textures.door;
		draw_ceiling(image, wall.start, scene.ceiling_color, x);
		draw_wall(image, x, wall, state);
		draw_floor(image, wall.end, scene.floor_color, x);
		x++;
	}
}
