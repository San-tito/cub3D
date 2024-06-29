/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:21:05 by droied            #+#    #+#             */
/*   Updated: 2024/06/29 17:31:37 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/************IMPORTANT FUNCTIONS***************/

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

/***********************************************/

/****************TEST_FUNCTIONS*****************/
static void	draw_circle_aux(mlx_image_t *img, int xc, int yc, int x, int y)
{
	/*top*/
	mlx_put_pixel(img, xc + x, yc + y, 0xFFFFFF);
	mlx_put_pixel(img, xc - x, yc + y, 0xFFFFFF);
	/*bot*/
	mlx_put_pixel(img, xc + x, yc - y, 0xFFFFFF);
	mlx_put_pixel(img, xc - x, yc - y, 0xFFFFFF);
	/*right*/
	mlx_put_pixel(img, xc + y, yc + x, 0xFFFFFF);
	mlx_put_pixel(img, xc + y, yc - x, 0xFFFFFF);
	/*left*/
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
	t_vec map;
	t_vec draw;
	map.x = MINI_M_X;
	map.y = MINI_M_Y;
	double x, y, dx, dy, p, xi, yi, k;
	dx = fabs(p2.x - p1.x);
	dy = fabs(p2.y - p1.y);
	if (dx > dy)
		p = dx;
	else
		p = dy;
	xi = dx / p;
	yi = dy / p;
	if (p1.x > p2.x)
		xi *= (-1);
	if (p1.y > p2.y)
		yi *= (-1);
	x = p1.x;
	y = p1.y;
	for (k = 1; k <= p; k++)
	{
		x += xi;
		y += yi;
		draw.x = x;
		draw.y = y;
		if (in_bounds(map, draw, MINI_M_SIZE))
			mlx_put_pixel(core.img, x, y, 0x008A2BE2);
	}
}

void	draw_character(t_core core, t_vec3 c, int base)
{
	t_vec init;
	t_vec final;
	(void)base;	
	c.dx = cos(c.a) * 5;
	c.dy = sin(c.a) * 5;
	init.x = c.x;
	init.y = c.y;
	final.x = c.dx + c.x;
	final.y = c.dy + c.y;
	dda_line(core, init, final);
}

void	draw_minimap(t_core core)
{
	t_minimap	minimap;

	core.img = mlx_new_image(core.mlx, WIDTH, HEIGHT);
	if (core.img == 0)
		libx_error("mlx error");
	minimap = core.scene.minimap;
	draw_circle(core.img, minimap.m, MINI_M_SIZE);
	draw_character(core, minimap.p, MINI_P_SIZE);
	if (core.img == 0 || (mlx_image_to_window(core.mlx, core.img, 0, 0) < 0))
		libx_error("mlx error");
}
