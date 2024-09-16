/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:40 by droied            #+#    #+#             */
/*   Updated: 2024/09/16 11:58:05 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	draw_player(mlx_image_t *img, t_ivec c, int radius, int color) 
{
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < radius << 1 && i + c.y < (int32_t)img->height) 
	{
		j = 0;
		while (j < radius << 1 && j + c.x < (int32_t)img->width) 
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

void	draw_minimap(mlx_image_t *img, t_scene scene, t_ivec c, int radius, int color) 
{
	(void)scene;
	unsigned short int	i;
	unsigned short int	j;

	t_fvec m;
	m.y = 0;
	i = 0;
	j = 0;
	while (i < radius << 1 && i + c.y < (int32_t)img->height) 
	{
		m.x = 0;
		j = 0;
		while (j < radius << 1 && j + c.x < (int32_t)img->width) 
		{
			if (((j - radius) * (j - radius)) +
			((i - radius) * (i - radius)) <
			(radius * radius))
			{
					put_pixel(img, j + c.x, i + c.y, color);
				 if (scene.map.cells[(int)m.y][(int)m.x] == SPACE)	
					put_pixel(img, j + c.x, i + c.y, 0xFFFFFFFF);
			}
			j++;
			if (j % 20 == 0 && m.x < scene.map.cols - 1)
			{

				m.x++;
			 // printf("m.x %i\n", (int)m.x);
			}
		}
		i++;
		if (i % 20 == 0 && m.y < scene.map.rows - 1)
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
	minimap.radius = minimap.pos.x >> 1;
	int color;
	color = create_rgb(0, 0, 0, 100);
	draw_minimap(image, scene, minimap.pos, minimap.pos.x * 10, color);
	minimap.pos.x += 100;
	minimap.pos.y += 100;
	draw_player(image, minimap.pos, 5, 0x0000FFFF);
}
