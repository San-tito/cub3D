/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:40 by droied            #+#    #+#             */
/*   Updated: 2024/09/13 20:36:24 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void	draw_circle_aux(mlx_image_t *img, int xc, int yc, int x, int y)
{
	put_pixel(img, xc + x, yc + y, 0xFF00FFFF);
	put_pixel(img, xc - x, yc + y, 0xFF00FFFF);
	put_pixel(img, xc + x, yc - y, 0xFF00FFFF);
	put_pixel(img, xc - x, yc - y, 0xFF00FFFF);
	put_pixel(img, xc + y, yc + x, 0xFF00FFFF);
	put_pixel(img, xc + y, yc - x, 0xFF00FFFF);
	put_pixel(img, xc - y, yc + x, 0xFF00FFFF);
	put_pixel(img, xc - y, yc - x, 0xFF00FFFF);
}

static void	draw_circle(mlx_image_t *img, t_ivec c, int radius)
{
	int	x;
	int	y;
	int	d;

	x = 0;
	y = radius;
	d = 3 - 2 * radius;
	while (x <= y)
	{
		draw_circle_aux(img, c.x, c.y, x, y);
		x++;
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
	}
}

static int	in_bounds(t_ivec c, t_ivec n, int r)
{
	int	square_distance;

	square_distance = pow((n.x - c.x), 2) + pow((n.y - c.y), 2);
	return (square_distance <= pow(r, 2));
}

static int fill_circle(mlx_image_t *image, t_scene scene, t_ivec map, t_ivec pixel, uint32_t radius)
{
	if (!in_bounds(pixel, map, radius))
		return (1);
	(void)scene;
	put_pixel(image, pixel.x, pixel.y, 0xFF00FFFF);
	if (++pixel.x && fill_circle(image, scene, map, pixel, radius) == 0)
		return (0);
	// if (--pixel.x && fill_circle(image, scene, map, pixel, radius) == 0) 
		// return (-1);
	// if (++pixel.y && fill_circle(image, scene, map, pixel, radius) == 0)
		// return (0);
	// if (--pixel.y && fill_circle(image, scene, map, pixel, radius) == 0)
		// return (0);
	return (1);
}

void	minimap(mlx_image_t *image, t_scene *scene)
{
	t_minimap minimap;

	minimap.pos.x = image->width / 8;
	minimap.pos.y = image->height / 6;
	minimap.radius = minimap.pos.x / 2;
	draw_circle(image, minimap.pos, minimap.radius);
	fill_circle(image, *scene, minimap.pos, minimap.pos, minimap.radius);
}
