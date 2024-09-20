/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:40 by droied            #+#    #+#             */
/*   Updated: 2024/09/20 16:52:00 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

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

    while (true) 
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

static void draw_circle(mlx_image_t *img,t_ivec c, int radius)
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
				put_pixel(img, j + c.x, i + c.y, 0x000000FF);
			 }
			j++;
		}
		i++;
	}
}

static void	draw_player(mlx_image_t *img, t_scene scene, int radius)
{
	t_fvec rot;
	t_ivec beg;
	t_ivec end;


	draw_circle(img, scene.minimap.player, radius);
	rot.x = cos(scene.player.a) * 5; 
	rot.y = sin(scene.player.a) * 5;

	beg.x = scene.minimap.player.x + (radius); 
	beg.y = scene.minimap.player.y + (radius);
	end.x = beg.x + rot.x * 5;
	end.y = beg.y + rot.y * 5;
	draw_line(img, beg, end);
}

static void draw_minimap(mlx_image_t *img, t_scene scene, t_ivec c, int radius)
{
    float x;
    t_ivec pos;
    x = scene.minimap.step.x;
    pos.y = scene.player.pos.y;

    while (pos.y < radius << 1 && pos.y + c.y < (int32_t)img->height)
    {
        pos.x = scene.player.pos.x;
        scene.minimap.step.x = x;
        while (pos.x < radius << 1 && pos.x + c.x < (int32_t)img->width)
        {
            if (((pos.x - radius) * (pos.x - radius)) + ((pos.y - radius) * (pos.y - radius)) < (radius * radius))
            {
                if (scene.minimap.step.y < scene.map.rows && scene.minimap.step.x < scene.map.cols 
                    && scene.map.cells[(int)scene.minimap.step.y][(int)scene.minimap.step.x] == SPACE)
                {
                    put_pixel(img, pos.x + scene.minimap.step.x, pos.y + scene.minimap.step.y, 0xFFFFFFFF);
                }
            }
            scene.minimap.step.x += (float)scene.map.cols / img->width;
            pos.x++;
        }
        scene.minimap.step.y += (float)scene.map.rows / img->height;
        pos.y++;
    }
}

void	minimap(mlx_image_t *image, t_scene scene)
{
	int32_t player_size;

	player_size = scene.minimap.radius >> 4;
	scene.minimap.step.x = scene.player.pos.x - 1.8; // - 3.8; 
	scene.minimap.step.y = scene.player.pos.y - 1.5; //- 2.5;
	draw_minimap(image, scene, scene.minimap.pos, scene.minimap.radius);
	draw_player(image, scene, player_size);
}
