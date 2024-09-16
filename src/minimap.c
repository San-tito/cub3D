/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:40 by droied            #+#    #+#             */
/*   Updated: 2024/09/16 13:07:33 by deordone         ###   ########.fr       */
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

t_ivec	draw_minimap(mlx_image_t *img, t_scene scene, t_ivec c, int radius, int color) 
{
	t_fvec m;
	t_ivec pos;
	m.y = 0;
	pos.y = 0;
	while (pos.y < radius << 1 && pos.y + c.y < (int32_t)img->height) 
	{
		m.x = 0;
		pos.x = 0;
		while (pos.x < radius << 1 && pos.x + c.x < (int32_t)img->width) 
		{
			if (((pos.x - radius) * (pos.x - radius)) +
			((pos.y - radius) * (pos.y - radius)) <
			(radius * radius))
			{
					put_pixel(img, pos.x + c.x, pos.y + c.y, color);
				 if (scene.map.cells[(int)m.y][(int)m.x] == SPACE)	
					put_pixel(img, pos.x + c.x, pos.y + c.y, 0xFFFFFFFF);
			}
			pos.x++;
			if (pos.x % 20 == 0 && m.x < scene.map.cols - 1)
			{

				m.x++;
			 // printf("m.x %i\n", (int)m.x);
			}
		}
		pos.y++;
		if (pos.y % 20 == 0 && m.y < scene.map.rows - 1)
		{
			m.y++;
			// printf("m.y %i\n", (int)m.y);
		}
	}
	return (pos);
}

/*int	create_rgb(double r, double g, double b, int a)
{
	r = r / 255 * 0.5 * -0.1;
	g = g / 255 * 0.5 * -0.1;
	b = b / 255 * 0.5 * -0.1;
	return ((int)r << 24 | (int)g << 16 | (int)b << 8 | a);
}*/

void	minimap(mlx_image_t *image, t_scene scene)
{
	t_minimap minimap;

	minimap.pos.x = image->width / 136;
	minimap.pos.y = image->height / 76;
	minimap.radius = minimap.pos.x;
	minimap.pos = draw_minimap(image, scene, minimap.pos, minimap.radius * 10, 0x000000FF);
	minimap.pos.x = (minimap.pos.x >> 1) + (minimap.radius >> 1);
	minimap.pos.y = (minimap.pos.y >> 1) + (minimap.radius >> 1);
	draw_player(image, minimap.pos, minimap.radius >> 1, 0x0000FFFF);
}
