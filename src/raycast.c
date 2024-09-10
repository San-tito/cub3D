/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:56:51 by deordone          #+#    #+#             */
/*   Updated: 2024/08/21 19:51:36 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "raycast.h"

static void set_values(t_ray *ray, int x, t_player player, mlx_image_t img)
{
	ray->cam_x = 2 * x /(double)img.width -1;
	ray->dir.x = player.dir.x + player.plane.x * ray->cam_x; 
	ray->dir.y = player.dir.y + player.plane.y * ray->cam_x;
	ray->map.x = (int)player.pos.x;
	ray->map.y = (int)player.pos.y;
	ray->deltadist.x = fabs(1 / ray->dir.x);
	ray->deltadist.y = fabs(1 / ray->dir.y);
	ray->sidedist.x = 0;
	ray->sidedist.y = 0;
}

static void set_dda(t_ray *ray, t_player player)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;	
		ray->sidedist.x = (player.pos.x - ray->map.x) * ray->deltadist.x;
	}
	else 
	{
		ray->step.x = 1;	
		ray->sidedist.x = (ray->map.x + 1.0 - player.pos.x) * ray->deltadist.x;	
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;	
		ray->sidedist.y = (player.pos.y - ray->map.y) * ray->deltadist.y;
	}
	else 
	{
		ray->step.y = 1;	
		ray->sidedist.y = (ray->map.y + 1.0 - player.pos.y) * ray->deltadist.y;
	}
}

static void	dda(t_ray *ray, t_scene scene)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else 
		{	
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (ray->map.y < 0.25 || ray->map.x < 0.25 || ray->map.y > scene.map.cols - 0.25 || ray->map.x > scene.map.rows - 1.25)
			break ;
		else if (scene.map.cells[ray->map.y][ray->map.x] == '1')
			hit = 1;
	}
}

static void compute_wall(t_ray *ray, t_player player, mlx_image_t *img)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist.x - ray->deltadist.x);
	else
		ray->wall_dist = (ray->sidedist.y - ray->deltadist.y);
	if (ray->wall_dist < 0)
		ray->wall_dist = 0.0001;
	ray->wall.y = (int)(img->height / ray->wall_dist);
	ray->wall_start = -(ray->wall.y) / 2 + img->height / 2;
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = ray->wall.y / 2 + img->height / 2;
	if (ray->wall_end >= img->height)
		ray->wall_end = img->height - 1;
	if (ray->side == 0)
		ray->wall.x = player.pos.y + ray->wall_dist * ray->dir.y;
	else
		ray->wall.x = player.pos.x + ray->wall_dist * ray->dir.x;
	ray->wall.x -= floor(ray->wall.x);
}

void raycast(mlx_image_t *image, t_scene scene)
{
	t_ray 		ray;
	int32_t		x;
	
	x = 0;
	while (x < (int32_t)image->width)
	{
		set_values(&ray, x, scene.player, *image);
		set_dda(&ray, scene.player);
		dda(&ray, scene);
		compute_wall(&ray, scene.player, image);

		/*Drawing tests*/
		int32_t y;
		y = ray.wall_start;
		if (x == 0)
			print_ray(&ray);
		while (y <= ray.wall_end)
		{
			mlx_put_pixel(image, x, y, 0x00FFFFFF);
			y++;
		}
		x++;
	}
}
