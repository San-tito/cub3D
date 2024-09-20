/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:40 by droied            #+#    #+#             */
/*   Updated: 2024/09/20 08:16:19 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void	draw_player(mlx_image_t *img, t_ivec c, int radius)
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
/* se ve bonito pero utiliza numeros magicos
static void	draw_minimap(mlx_image_t *img, t_scene scene, t_ivec c, int radius)
{
	float x;
	t_ivec	pos;
	x = scene.minimap.step.x;
	pos.y = scene.player.pos.y;

	while (pos.y < radius << 1 && pos.y + c.y < (int32_t)img->height)
	{
		pos.x = scene.player.pos.x;
		scene.minimap.step.x = x;
		while (pos.x < radius << 1 && pos.x + c.x < (int32_t)img->width)
		{
			if (((pos.x - radius) * (pos.x - radius)) + ((pos.y - radius)
					* (pos.y - radius)) < (radius * radius))
			{
				if (scene.minimap.step.y < scene.map.rows && scene.minimap.step.x < scene.map.cols && scene.map.cells[(int)scene.minimap.step.y][(int)scene.minimap.step.x] == SPACE)
					put_pixel(img, pos.x + scene.minimap.step.x, pos.y + scene.minimap.step.y, 0xFFFFFFFF);
			}
			scene.minimap.step.x += 0.01999;
			pos.x++;
		}
		scene.minimap.step.y += 0.01999;
		pos.y++;
		printf("step -> {%f} {%f}\n",scene.minimap.step.x, scene.minimap.step.y);
	}
}
*/

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
                    put_pixel(img, pos.x + c.x, pos.y + c.y, 0xFFFFFFFF);
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
	scene.minimap.step.x = scene.player.pos.x - 3.2;
	scene.minimap.step.y = scene.player.pos.y - 2;
	draw_minimap(image, scene, scene.minimap.pos, scene.minimap.radius);
	draw_player(image, scene.minimap.player, player_size);
}
