/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:21:05 by droied            #+#    #+#             */
/*   Updated: 2024/07/06 18:55:06 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/************IMPORTANT FUNCTIONS***************/
/*
int	div2(const int dividend)
{
	return (dividend >> 1);
}

int	ft_div(const int dividend, const int divider)
{
	int	quotient;
	int	tmp_divider;
	int	tmp_dividend;

	quotient = 0;
	tmp_divider = (int)divider;
	tmp_dividend = (int)dividend;
	if (divider == 0)
		return (-1);
	while (tmp_divider <= tmp_dividend)
		tmp_divider <<= 1;
	while (tmp_divider > divider)
	{
		tmp_divider >>= 1;
		quotient <<= 1;
		if (tmp_dividend >= tmp_divider)
		{
			tmp_dividend -= tmp_divider;
			quotient |= 1;
		}
	}
	return (quotient);
}

float	deg2rad(int degrees)
{
	return (degrees * PI / 180);
}

int	in_bounds(t_vec c, t_vec n, int r)
{
	int	square_distance;

	square_distance = pow((n.x - c.x), 2) + pow((n.y - c.y), 2);
	return (square_distance <= pow(r, 2));
}


static void	draw_circle_aux(mlx_image_t *img, int xc, int yc, int x, int y)
{
	mlx_put_pixel(img, xc + x, yc + y, 0xFFFFFF);
	mlx_put_pixel(img, xc - x, yc + y, 0xFFFFFF);
	mlx_put_pixel(img, xc + x, yc - y, 0xFFFFFF);
	mlx_put_pixel(img, xc - x, yc - y, 0xFFFFFF);
	mlx_put_pixel(img, xc + y, yc + x, 0xFFFFFF);
	mlx_put_pixel(img, xc + y, yc - x, 0xFFFFFF);
	mlx_put_pixel(img, xc - y, yc + x, 0xFFFFFF);
	mlx_put_pixel(img, xc - y, yc - x, 0xFFFFFF);
}

void	draw_circle(mlx_image_t *img, t_vec c, int radius)
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

void	dda_line(t_core core, t_vec p1, t_vec p2)
{
	t_vec	draw;
	t_vec	steps;
	t_vec	delta;

	delta.x = fabs(p2.x - p1.x);
	delta.y = fabs(p2.y - p1.y);
	draw.x = p1.x;
	draw.y = p1.y;
	if (delta.x > delta.y)
		steps.x = delta.x;
	else
		steps.x = delta.y;
	delta.x = delta.x / steps.x;
	delta.y = delta.y / steps.x;
	if (p1.x > p2.x)
		delta.x *= (-1);
	if (p1.y > p2.y)
		delta.y *= (-1);
	steps.y = -1;
	while (++steps.y <= steps.x)
	{
		if (in_bounds(p1, draw, core.scene.minimap.size))
		{
			mlx_put_pixel(core.img, draw.x - 2, draw.y, 0x008A2BE2);
			mlx_put_pixel(core.img, draw.x - 1, draw.y, 0x008A2BE2);
			mlx_put_pixel(core.img, draw.x, draw.y, 0x008A2BE2);
			mlx_put_pixel(core.img, draw.x + 1, draw.y, 0x008A2BE2);
			mlx_put_pixel(core.img, draw.x + 2, draw.y, 0x008A2BE2);
			mlx_put_pixel(core.img, draw.x + 3, draw.y, 0x008A2BE2);
		}
		draw.x += delta.x;
		draw.y += delta.y;
	}
}

void	draw_character(t_core core, t_vec3 c)
{
	t_vec	init;
	t_vec	final;

	c.dx = cos(c.a) * 5;
	c.dy = sin(c.a) * 5;
	init.x = c.x;
	init.y = c.y;
	final.x = c.x + (c.dx * 3);
	final.y = c.y + (c.dy * 3);
	dda_line(core, init, final);
}

void	draw_minimap(t_core *core)
{
	t_minimap	minimap;

	minimap = core->scene.minimap;
	draw_circle(core->img, minimap.m, core->scene.minimap.size);
	draw_character(*(core), minimap.p);
	if (core->img == 0 || (mlx_image_to_window(core->mlx, core->img, 0, 0) < 0))
		libx_error("mlx error");
}*/
