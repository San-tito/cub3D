/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:24:16 by droied            #+#    #+#             */
/*   Updated: 2024/07/06 19:05:46 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line(mlx_image_t *img, t_vec2 v0, t_vec2 v1, int color)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;

	dx = abs(v1.x - v0.x);
	sx = (v0.x < v1.x) + (v0.x > v1.x) * -1;
	dy = -abs(v1.y - v0.y);
	sy = (v0.y < v1.y) + (v0.y > v1.y) * -1;
	err = dx + dy;
	while (!(v0.x == v1.x && v0.y == v1.y))
	{
		mlx_put_pixel(img, v0.x, v0.y, color);
		if (err << 1 >= dy && v0.x != v1.x)
		{
			err += dy;
			v0.x += sx;
		}
		if (err << 1 <= dx && v0.y != v1.y)
		{
			err += dx;
			v0.y += sy;
		}
	}
}
