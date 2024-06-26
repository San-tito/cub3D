/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:21:05 by droied            #+#    #+#             */
/*   Updated: 2024/06/26 03:05:39 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/************IMPORTANT FUNCTIONS***************/

int div2 (const int dividend)
{
	return (dividend >> 1);
}

int ft_div (const int dividend, const int divider)
{
	int quotient = 0;
    int tmp_divider = (int)divider;
    int tmp_dividend = (int)dividend;
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

float dtor (int degrees)
{
	return ((float)ft_div(degrees * PI, 180));
}

int in_bounds(t_vec c, t_vec n, int r)
{
	int square_distance;
	square_distance = pow((n.x - c.x), 2) + pow((n.y - c.y), 2);
	return (square_distance <= pow(r,2));
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
			d = d + 4 * x + 6 ;
	}
}

/*
void	draw_character(t_core core, t_vec3 c, int base)
{
	t_vec start;
	t_vec end;
	int x;
	
	if (c.a < 0)
		c.a += 2 * PI;
	else if (c.a > 2 * PI)
		c.a -= 2 * PI;
	c.dx = cos(dtor(c.a));
	c.dy = sin(dtor(c.a));
	start.x = c.x - div2(base);
	start.y = c.y - base;
	end.x = c.x + div2(base);
	end.y = c.y + base;
	while (start.y < end.y)
	{
		x = start.x;
		while (x < end.x)
		{
			x++;
			mlx_put_pixel(core.img, x, start.y, 0xFFFFFF);
		}
		start.y++;
	}
	start.x = c.x - base;
	start.y = (c.y + base) - div2(base);
	end.x = c.x + base;
	end.y = (c.y + base) + div2(base);
	while (start.y < end.y)
	{
		x = start.x - 1;
		while (++x < end.x)
			mlx_put_pixel(core.img, x, start.y, 0xFFFFFF);
		start.y++;
	}
}*/

void	draw_character(t_core core, t_vec3 c, int base)
{
	t_vec start;
	t_vec end;
	int x;

	start.x = c.x - div2(base);
	start.y = c.y - base;
	end.x = c.x + div2(base);
	end.y = c.y + base;
	while (start.y < end.y)
	{
		x = start.x - 1;
		while (++x < end.x)
			mlx_put_pixel(core.img, x, start.y, 0xFFFFFF);
		start.y++;
	}
	start.x = c.x - base;
	start.y = (c.y + base) - div2(base);
	end.x = c.x + base;
	end.y = (c.y + base) + div2(base);
	while (start.y < end.y)
	{
		x = start.x - 1;
		while (++x < end.x)
			mlx_put_pixel(core.img, x, start.y, 0xFFFFFF);
		start.y++;
	}
}

void draw_minimap(t_core core)
{
	t_minimap minimap = {};
	int		r;

	r = 100;
	minimap.m.x = MINI_M_X;
	minimap.m.y = MINI_M_Y;
	minimap.p.x = minimap.m.x;
	minimap.p.y = minimap.m.y;
	minimap.p.dx = cos(dtor(minimap.p.a));
	minimap.p.dy = sin(dtor(minimap.p.a));
	draw_circle(core.img, minimap.m, r);
	draw_character(core, minimap.p, MINI_P_SIZE);
	if (core.img == 0 || (mlx_image_to_window(core.mlx, core.img, 0, 0) < 0))
		libx_error("mlx error");
}
