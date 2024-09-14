/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:40 by droied            #+#    #+#             */
/*   Updated: 2024/09/14 19:35:34 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
/*
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
}*/

void	draw_circle(mlx_image_t *img, t_scene scene, t_ivec c, int radius, int color) 
{
	(void)scene;
	unsigned short int	i;
	unsigned short int	j;
	t_fvec m;
	// t_ivec scale;
	// scale.x = 200 + c.x / scene.map.rows;
	// scale.y = 200 + c.y / scene.map.cols;
	m.y = 0;
	
	 // printf("m.x -> %f\n m.y -> %f\n", m.x, m.y);

	i = 0;
		j = 0;
	while (i < radius * 2 && i + c.y < (int32_t)img->height) 
	{
		m.x = 0;
		j = 0;
		while (j < radius * 2 && j + c.x < (int32_t)img->width) 
		{
			if (((j - radius) * (j - radius)) +
			((i - radius) * (i - radius)) <
			(radius * radius))
			{
				 if (scene.map.cells[(int)m.y][(int)m.x] == SPACE)	
					put_pixel(img, j + c.x, i + c.y, color);
				 else if (scene.map.cells[(int)m.y][(int)m.x] == WALL)	
					put_pixel(img, j + c.x, i + c.y, 0xFF00FFFF);
			}
			j++;
			if (j % 10 == 0 && m.x < scene.map.cols - 1)
			{

				m.x++;
			 // printf("m.x %i\n", (int)m.x);
			}
		}
		i++;
		if (i % 10 == 0 && m.y < scene.map.rows - 1)
		{
			m.y++;
			// printf("m.y %i\n", (int)m.y);
		}
	}
}
/*
static int	in_bounds(t_ivec c, t_ivec n, int r)
{
	int	square_distance;

	square_distance = pow((n.x - c.x), 2) + pow((n.y - c.y), 2);
	return (square_distance <= pow(r, 2));
}*/
/*
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
}*/

int	create_rgb(double r, double g, double b, int a)
{
	r = r / 255 * 0.5 * -0.1;
	g = g / 255 * 0.5 * -0.1;
	b = b / 255 * 0.5 * -0.1;
	return ((int)r << 24 | (int)g << 16 | (int)b << 8 | a);
}

void	minimap(mlx_image_t *image, t_scene scene)
{
	t_minimap minimap;

	// minimap.pos.x = image->width / 8;
	// minimap.pos.y = image->height / 6;
	minimap.pos.x = image->width / 136;
	minimap.pos.y = image->height / 76;
	minimap.radius = minimap.pos.x / 2;
	int color;
	color = create_rgb(0, 0, 0, 50);
	draw_circle(image, scene, minimap.pos, minimap.pos.x * 10, color);
	//fill_circle(image, *scene, minimap.pos, minimap.pos, minimap.radius);
}
