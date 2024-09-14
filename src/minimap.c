/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:40 by droied            #+#    #+#             */
/*   Updated: 2024/09/14 19:53:44 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	draw_circle(mlx_image_t *img, t_ivec c, int radius, int color) 
{
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < radius * 2 && i + c.y < (int32_t)img->height) 
	{
		j = 0;
		while (j < radius * 2 && j + c.x < (int32_t)img->width) 
		{
			if (((j - radius) * (j - radius)) +
			((i - radius) * (i - radius)) <
			(radius * radius))
			{
				put_pixel(img, j + c.x, i + c.y, color);
			}
			j++;
		}
		i++;
	}
}

void	draw_circle2(mlx_image_t *img, t_scene scene, t_ivec c, int radius, int color) 
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
					put_pixel(img, j + c.x, i + c.y, 0xFFFFFFFF);
				 else if (scene.map.cells[(int)m.y][(int)m.x] == WALL)	
					put_pixel(img, j + c.x, i + c.y, color);
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

	minimap.pos.x = image->width / 136;
	minimap.pos.y = image->height / 76;
	minimap.radius = minimap.pos.x / 2;
	int color;
	color = create_rgb(0, 0, 0, 100);
	draw_circle2(image, scene, minimap.pos, minimap.pos.x * 10, color);
	minimap.pos.x += 100;
	minimap.pos.y += 100;
	draw_circle(image, minimap.pos, 5, 0x0000FFFF);
}
