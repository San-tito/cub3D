/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:40 by droied            #+#    #+#             */
/*   Updated: 2024/09/25 12:29:14 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	steps(t_ivec *err, t_ivec *beg, t_ivec s, t_ivec d)
{
	err->y = err->x;
	if (err->y > -d.x)
	{
		err->x -= d.y;
		beg->x += s.x;
	}
	if (err->y < d.y)
	{
		err->x += d.x;
		beg->y += s.y;
	}
}

static void	draw_line(mlx_image_t *img, t_ivec beg, t_ivec end)
{
	t_ivec	s;
	t_ivec	d;
	t_ivec	err;

	d.x = abs(end.x - beg.x);
	d.y = abs(end.y - beg.y);
	s.x = -1;
	s.y = -1;
	if (beg.x < end.x)
		s.x = 1;
	if (beg.y < end.y)
		s.y = 1;
	err.x = -d.y;
	if (d.x > d.y)
		err.x = d.x;
	err.x = err.x >> 1;
	while (42)
	{
		put_pixel(img, beg.x, beg.y, 0x000000FF);
		if (beg.x == end.x && beg.y == end.y)
			break ;
		steps(&err, &beg, s, d);
	}
}

static void	draw_player(mlx_image_t *img, t_scene scene, int radius)
{
	t_ivec	tip;
	t_ivec	left;
	t_ivec	right;
	t_ivec	center;

	center.x = scene.minimap.player.x;
	center.y = scene.minimap.player.y;
	tip.x = center.x + scene.player.dir.x * (radius);
	tip.y = center.y + scene.player.dir.y * (radius);
	left.x = center.x - scene.player.plane.x * (radius);
	left.y = center.y - scene.player.plane.y * (radius);
	right.x = center.x + scene.player.plane.x * (radius);
	right.y = center.y + scene.player.plane.y * (radius);
	draw_line(img, left, tip);
	draw_line(img, right, tip);
	center.x = center.x + (tip.x - center.x) * 0.4;
	center.y = center.y + (tip.y - center.y) * 0.4;
	draw_line(img, left, center);
	draw_line(img, right, center);
}

static void	draw_minimap(mlx_image_t *img, t_scene scene, t_ivec map, int r)
{
	t_fvec	s;
	t_ivec	pos;

	pos.y = 0;
	while (pos.y < r << 1)
	{
		pos.x = 0;
		while (pos.x < r << 1)
		{
			if (pow(pos.x - r, 2) + pow(pos.y - r, 2) < pow(r, 2))
			{
				s.x = (pos.x - r) * scene.minimap.scale.x
					+ scene.minimap.step.x;
				s.y = (pos.y - r) * scene.minimap.scale.y
					+ scene.minimap.step.y;
				if (s.y >= 0 && s.y < scene.map.rows && s.x >= 0
					&& s.x < scene.map.cols
					&& scene.map.cells[(int)s.y][(int)s.x] == SPACE)
					put_pixel(img, pos.x + map.x, pos.y + map.y, 0xFFFFFFFF);
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	minimap(mlx_image_t *image, t_scene scene)
{
	draw_sight(image);
	scene.minimap.step.x = scene.player.pos.x;
	scene.minimap.step.y = scene.player.pos.y;
	draw_minimap(image, scene, scene.minimap.pos, scene.minimap.radius);
	draw_player(image, scene, scene.minimap.radius >> 4);
}
