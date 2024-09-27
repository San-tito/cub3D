/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sight.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 23:55:42 by droied            #+#    #+#             */
/*   Updated: 2024/09/21 00:06:14 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	midpoint_aux(mlx_image_t *img, t_ivec c, t_ivec c2, int color)
{ 
	put_pixel(img, c.x + c2.x, c.y + c2.y, color);
	put_pixel(img, c.x - c2.x, c.y + c2.y, color);
	put_pixel(img, c.x + c2.x, c.y - c2.y, color);
	put_pixel(img, c.x - c2.x, c.y - c2.y, color);
	put_pixel(img, c.x + c2.y, c.y + c2.x, color);
	put_pixel(img, c.x + c2.y, c.y - c2.x, color);
	put_pixel(img, c.x - c2.y, c.y + c2.x, color);
	put_pixel(img, c.x - c2.y, c.y - c2.x, color);
}

void	midpoint(mlx_image_t *img, t_ivec c, int radius, int color)
{
	t_ivec c2;
	int	d;

	c2.x = 0;
	c2.y = radius;
	d =  radius * radius;
	while (c2.x <= c2.y)
	{
		midpoint_aux(img, c, c2, color);
		c2.x++;
		if (d > 0)
		{
			c2.y--;
			d = d  * (c2.x - c2.y) + 10;
		}
		else
			d = d * c2.x + 1;
	}
}

void	draw_sight(mlx_image_t *image)
{
	t_minimap sight;

	sight.pos.x = (image->width >> 1);
	sight.pos.y = (image->height >> 1);
	sight.radius = (sight.pos.x - sight.pos.y) >> 6;
	while (sight.radius != 0)
		midpoint(image, sight.pos, sight.radius--, 0xFF0000FF);
}
