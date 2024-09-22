/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:40 by droied            #+#    #+#             */
/*   Updated: 2024/09/23 00:01:34 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// para debugear cuando se me de la gana de arreglar los steps
//printf("step -> {%f} {%f}\n",scene.minimap.step.x, scene.minimap.step.y);

static void draw_line(mlx_image_t *img, t_ivec beg, t_ivec end) 
{
	int32_t err;
	int32_t e2;
	t_ivec d;
	t_ivec s;

	d.x = abs(end.x - beg.x);
	d.y = abs(end.y - beg.y);
	s.x = -1;
	s.y = -1;
	if (beg.x < end.x)
		s.x = 1;
	if (beg.y < end.y)
		s.y = 1;
	err = -d.y;
	if (d.x > d.y)
		err = d.x;
	err = err >> 1;

    while (42) 
	{
        put_pixel(img, beg.x, beg.y, 0x000000FF);
        if (beg.x == end.x && beg.y == end.y)
            break;
        e2 = err;
        if (e2 > -d.x) 
		{
        	err -= d.y;
            beg.x += s.x;
        }
        if (e2 < d.y) 
		{
            err += d.x;
            beg.y += s.y;
        }
    }
}  
/*
static void draw_square(mlx_image_t *img, t_ivec c, int radius)
{
	unsigned short int	y;
	unsigned short int	x;

	y = 0;
	while (y < radius << 1)
	{
		x = 0;
		while (x < radius << 1)
		{
			put_pixel(img, x + c.x, y + c.y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
}
*/
static void draw_circle(mlx_image_t *img, t_ivec c, int radius)
{
	unsigned short int	y;
	unsigned short int	x;

	y = 0;
	while (y < radius << 1)
	{
		x = 0;
		while (x < radius << 1)
		{
			if (pow(x - radius, 2) + pow(y - radius, 2) < pow(radius, 2))
				put_pixel(img, x + c.x, y + c.y, 0x000000FF);
			x++;
		}
		y++;
	}
}

static void	draw_player(mlx_image_t *img, t_scene scene, int radius)
{
	t_fvec rot;
	t_ivec beg;
	t_ivec end;

	scene.minimap.player.x -= radius;
	scene.minimap.player.y -= radius;
	draw_circle(img, scene.minimap.player, radius);
	rot.x = cos(scene.player.a) * 5; 
	rot.y = sin(scene.player.a) * 5;

	beg.x = scene.minimap.player.x + (radius); 
	beg.y = scene.minimap.player.y + (radius);
	end.x = beg.x + rot.x * 5;
	end.y = beg.y + rot.y * 5;
	draw_line(img, beg, end);
}

static void draw_minimap(mlx_image_t *img, t_scene scene, t_ivec map, int radius)
{
	t_fvec s;
    t_ivec pos;
	t_ivec draw;
	  float scale_x = (float)scene.map.cols / (float)(radius * 2);
    float scale_y = (float)scene.map.rows / (float)(radius * 2);

    pos.y = 0;
    while (pos.y < radius << 1)
    {
        pos.x = 0;
        while (pos.x < radius << 1)
        {
            if (pow(pos.x - radius, 2) + pow(pos.y - radius, 2) < pow(radius, 2))
        	{
 				s.x = (pos.x - radius) * scale_x + scene.minimap.step.x;
                s.y = (pos.y - radius) * scale_y + scene.minimap.step.y;
				draw.x = pos.x + map.x;
				draw.y = pos.y + map.y;
				  if (s.y >= 0 && s.y < scene.map.rows && s.x >= 0 && s.x < scene.map.cols 
                    && scene.map.cells[(int)scene.minimap.step.y][(int)scene.minimap.step.x] == SPACE)
					  put_pixel(img, draw.x, draw.y, 0xFFFFFFFF);
            }
            pos.x++;
        }
        pos.y++;
    }
}

void	minimap(mlx_image_t *image, t_scene scene)
{
	scene.minimap.step.x = scene.player.pos.x; 
	scene.minimap.step.y = scene.player.pos.y;
	draw_sight(image);
	draw_minimap(image, scene, scene.minimap.pos, scene.minimap.radius);
	draw_player(image, scene, scene.minimap.radius >> 4);
}
