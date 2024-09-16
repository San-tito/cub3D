/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:40 by droied            #+#    #+#             */
/*   Updated: 2024/09/16 16:58:49 by deordone         ###   ########.fr       */
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
			if (((j - radius) * (j - radius)) + ((i - radius) * (i
						- radius)) < (radius * radius))
			{
				put_pixel(img, j + c.x, i + c.y, color);
			}
			j++;
		}
		i++;
	}
}

static t_ivec aux_minimap(mlx_image_t *img, t_ivec c, int radius)
{
	t_ivec p;

	p.y = 0;
	while (p.y < radius << 1 && p.y + c.y < (int32_t)img->height)
	{
		p.x = 0;
		while (p.x < radius << 1 && p.x + c.x < (int32_t)img->width)
			p.x++;
		p.y++;
	}
	return (p);
}

t_ivec	draw_minimap(mlx_image_t *img, t_scene scene, t_ivec c, int radius,
		int color)
{
	t_fvec	m;
	t_ivec	pos;
	t_ivec  aux;

	m.y = 0;
	aux = aux_minimap(img, c, radius);
	pos.y = scene.player.pos.y - 10;
	while (pos.y < radius << 1 && pos.y + c.y < (int32_t)img->height)
	{
		m.x = 0;
		pos.x = scene.player.pos.x - 10;
		//pos.x = scene.player.pos.x;
		while (pos.x < radius << 1 && pos.x + c.x < (int32_t)img->width)
		{
			if (((pos.x - radius) * (pos.x - radius)) + ((pos.y - radius)
					* (pos.y - radius)) < (radius * radius))
			{
				if (scene.map.cells[(int)m.y][(int)m.x] == SPACE)
					put_pixel(img, pos.x + c.x, pos.y + c.y, color);
			}
			pos.x++;
		if (pos.x % 10 == 0 && m.x < scene.map.cols - 1)
			 { 
				m.x++;
				// printf("m.x %i\n", (int)m.x);
			}
		}
		pos.y++;
		if (pos.y % 10 == 0 && m.y < scene.map.rows - 1)
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
	// el minimapa se renderiza teniendo en cuenta la pos y la dir del player
	// step by step
	// draw_minimap(image, scene) y depende de dir y pos <------------
	draw_minimap(image, scene, scene.minimap.pos, scene.minimap.radius,
		0xFFFFFFFF);
	draw_player(image, scene.minimap.pos, scene.minimap.radius >> 6,
		0x0000FFFF);
}
