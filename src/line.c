/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:24:16 by droied            #+#    #+#             */
/*   Updated: 2024/08/08 15:38:05 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	_change_brightness(int color, float br)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	if (br > 1.0)
		br = 1.0;
	red = (uint8_t)(br * ((color >> 24) & 0xFF));
	green = (uint8_t)(br * ((color >> 16) & 0xFF));
	blue = (uint8_t)(br * ((color >> 8) & 0xFF));
	return ((color & 0xFF000000) | ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue);
}

static void	plot(mlx_image_t *img, int x, int y, int color, float br)
{
	int	new_color;

	new_color = _change_brightness(color, br);
	mlx_put_pixel(img, x, y, new_color);
}

void	draw_line(mlx_image_t *img, t_vec2 v0, t_vec2 v1, int color)
{
	double	gradient;
	double	dx;
	double	dy;
	double	xend;
	double	yend;
	double	xgap;
	double	ygap;
	double	intery;
	double	interx;
	int		xpxl1;
	int		ypxl1;
	int		xpxl2;
	int		ypxl2;
	t_vec2	temp;

	dx = (double)v1.x - (double)v0.x;
	dy = (double)v1.y - (double)v0.y;
	if (fabs(dx) > fabs(dy))
	{
		if (v1.x < v0.x)
		{
			temp = v0;
			v0 = v1;
			v1 = temp;
		}
		gradient = dy / dx;
		xend = round(v0.x);
		yend = v0.y + gradient * (xend - v0.x);
		xgap = 1.0 - fmod(v0.x + 0.5, 1.0);
		xpxl1 = (int)xend;
		ypxl1 = (int)yend;
		plot(img, xpxl1, ypxl1, color, (1.0 - fmod(yend, 1.0)) * xgap);
		plot(img, xpxl1, ypxl1 + 1, color, fmod(yend, 1.0) * xgap);
		intery = yend + gradient;
		xend = round(v1.x);
		yend = v1.y + gradient * (xend - v1.x);
		xgap = fmod(v1.x + 0.5, 1.0);
		xpxl2 = (int)xend;
		ypxl2 = (int)yend;
		plot(img, xpxl2, ypxl2, color, (1.0 - fmod(yend, 1.0)) * xgap);
		plot(img, xpxl2, ypxl2 + 1, color, fmod(yend, 1.0) * xgap);
		for (int x = xpxl1 + 1; x < xpxl2; x++)
		{
			plot(img, x, (int)intery, color, 1.0 - fmod(intery, 1.0));
			plot(img, x, (int)intery + 1, color, fmod(intery, 1.0));
			intery += gradient;
		}
	}
	else
	{
		if (v1.y < v0.y)
		{
			temp = v0;
			v0 = v1;
			v1 = temp;
		}
		gradient = dx / dy;
		yend = round(v0.y);
		xend = v0.x + gradient * (yend - v0.y);
		ygap = 1.0 - fmod(v0.y + 0.5, 1.0);
		ypxl1 = (int)yend;
		xpxl1 = (int)xend;
		plot(img, xpxl1, ypxl1, color, (1.0 - fmod(xend, 1.0)) * ygap);
		plot(img, xpxl1 + 1, ypxl1, color, fmod(xend, 1.0) * ygap);
		interx = xend + gradient;
		yend = round(v1.y);
		xend = v1.x + gradient * (yend - v1.y);
		ygap = fmod(v1.y + 0.5, 1.0);
		ypxl2 = (int)yend;
		xpxl2 = (int)xend;
		plot(img, xpxl2, ypxl2, color, (1.0 - fmod(xend, 1.0)) * ygap);
		plot(img, xpxl2 + 1, ypxl2, color, fmod(xend, 1.0) * ygap);
		for (int y = ypxl1 + 1; y < ypxl2; y++)
		{
			plot(img, (int)interx, y, color, 1.0 - fmod(interx, 1.0));
			plot(img, (int)interx + 1, y, color, fmod(interx, 1.0));
			interx += gradient;
		}
	}
}
