/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:56:51 by deordone          #+#    #+#             */
/*   Updated: 2024/09/12 15:47:30 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "print.h"
#include "raycast.h"

static void	set_values(t_ray *ray, t_player player)
{
	ray->dir.x = player.pos.x  + player.dir.x + player.plane.x;
	ray->dir.y = player.pos.y  + player.dir.y + player.plane.y;
	ray->pos.x = (float)player.pos.x; 
	ray->pos.y = (float)player.pos.y;
	ray->deltadist.x = 1E30;
	ray->deltadist.y = 1E30;
	if (ray->dir.x != 0)
		ray->deltadist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y != 0)
		ray->deltadist.y = fabs(1 / ray->dir.y);
}

static void	set_dda(t_ray *ray, t_player player)
{
	ray->step.x = (ray->dir.x > 0) + ((ray->dir.x < 0) * -1);
	ray->step.y = (ray->dir.x > 0) + ((ray->dir.x < 0) * -1);

	if (ray->dir.x < 0)
		ray->sidedist.x = (player.pos.x - ray->pos.x) * ray->deltadist.x;
	else
 		ray->sidedist.x = (ray->pos.x + 1.0 - player.pos.x) * ray->deltadist.x;
	if (ray->dir.y < 0)
		ray->sidedist.y = (player.pos.y - ray->pos.y) * ray->deltadist.y;
	else
		ray->sidedist.y = (ray->pos.y + 1.0 - player.pos.y) * ray->deltadist.y;
}

static void	dda(t_ray *ray, t_scene scene)
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

		/* Check if the ray go outside of the boundaries of the map
		 * if (ray->pos.y < 0 || ray->pos.x < 0
			|| ray->pos.y > scene.map.cols || ray->pos.x > scene.map.rows)
			break ;*/
		if (scene.map.cells[(int32_t)ray->pos.y][(int32_t)ray->pos.x] > SPACE)
			hit++;
	}
}

static void	compute_wall(t_ray *ray, mlx_image_t *img)
{
	uint32_t height;

	height = img->height / 2;
	//wall distance
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist.x - ray->deltadist.x);
	else
		ray->wall_dist = (ray->sidedist.y - ray->deltadist.y);
	//start and end pixel
	ray->wall_height = (int)height / ray->wall_dist;
	ray->wall_height = ray->wall_height / 2;
	ray->wall_start = -(ray->wall_height) / 2 + height / 2;
	if (ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = ray->wall_height / 2 + height / 2;
	if (ray->wall_end >= img->height)
		ray->wall_end = height - 1;
}

static void draw_wall(mlx_image_t *image, uint32_t x, int32_t start, int32_t end, int32_t color)
{
	printf("Wall line [%i] [%i] \n", start, end);
	printf("Size pc [%u] [%u] \n", image->width, image->height);
	while (start < end)
	{
		mlx_put_pixel(image, x, start++, color);
	}
}

void	raycast(mlx_image_t *image, t_scene scene)
{
	t_ray	ray;
	uint32_t	x;

	x = 0;
	while (x < image->width)
	{
		set_values(&ray, scene.player);
		set_dda(&ray, scene.player);
		dda(&ray, scene);
		compute_wall(&ray, image);
		draw_wall(image, x, ray.wall_start, ray.wall_end, 0xFF00FFFF);
		if (x == 0)
			print_ray(&ray);
		x++;
	}
}
