/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:40 by droied            #+#    #+#             */
/*   Updated: 2024/09/17 19:33:51 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

// Ingredientes

//scene.player.pos = la posicion del jugador
//scene.player.dir = la direccion del jugador

//minimap.pos = posicion del renderizado del minimapa
//minimap.radius = el radio del minimapa 
//minimap.step = posicion del mapa dentro del minimapa (el step debe quedar de tal forma que cuando se llegue al 
//centro del circulo se este en la posicion scene.player.pos)
//minimap.dir = la direccion del minimapa es opuesta a la direccion del jugador, es decir si giro hacia la 
//derecha el minimapa debe girar hacia la izquierda.
//el spawn orient determina la direccion inicial del minimapa. 

void	draw_player(mlx_image_t *img, t_ivec c, int radius, int color)
{
	unsigned short int	i;
	unsigned short int	j;

	i = 0;
	while (i < radius << 1 && i + c.y < (int32_t)img->height)
	{
		j = 0;
		while (j < radius << 1 && j + c.x < (int32_t)img->width)
		{
		/*	if (((j - radius) * (j - radius)) + ((i - radius) * (i
						- radius)) < (radius * radius))
			{*/
				put_pixel(img, j + c.x, i + c.y, color);
			// }
			j++;
		}
		i++;
	}
}
/*
static t_ivec aux_minimap(mlx_image_t *img, t_ivec c, int radius)
{
	t_ivec p;

	p.y = 0;
	while (p.y < radius << 1 && p.y + c.y < (int32_t)img->height)
	{
		p.x = 0;
		while (p.x < radius << 1 && p.x + c.x < (int32_t)img->width)
			p.x++;
		p.y++;
	}
	return (p);
}
*/
t_ivec	draw_minimap(mlx_image_t *img, t_scene scene, t_ivec c, int radius,
		int color)
{
	t_ivec	pos;
	float x;
	x = scene.minimap.step.x;
	// t_ivec  aux;

	// aux = aux_minimap(img, c, radius);
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
				if (scene.map.cells[(int)scene.minimap.step.y][(int)scene.minimap.step.x] == SPACE)
					put_pixel(img, pos.y + scene.minimap.step.y, pos.x + scene.minimap.step.x, color);
			}
			scene.minimap.step.x += 0.005;
			pos.x++;
		}
		 scene.minimap.step.y += 0.005;
		pos.y++;
	printf("step -> {%f} {%f}\n",scene.minimap.step.x, scene.minimap.step.y);
	}
	return (pos);
}

/*int	create_rgb(double r, double g, double b, int a)
{
	r = r / 255 * 0.5 * -0.1;
	g = g / 255 * 0.5 * -0.1;
	b = b / 255 * 0.5 * -0.1;
	return ((int)r << 24 | (int)g << 16 | (int)b << 8 | a);
}*/
void	minimap(mlx_image_t *image, t_scene scene)
{
	// el minimapa se renderiza teniendo en cuenta la pos y la dir del player
	// step by step
	// draw_minimap(image, scene) y depende de dir y pos <------------
	// printf("dir -> {%f} {%f}\n",scene.player.dir.x, scene.player.dir.y);
	if (scene.player.spawn_orient == EAST)
		scene.player.dir.y = -1;
	if (scene.player.spawn_orient == NORTH)
		scene.player.dir.x = -1;
	if (scene.player.spawn_orient == WEST)
		scene.player.dir.y = 1;
	if (scene.player.spawn_orient == SOUTH)
		scene.player.dir.y = 1;
	scene.minimap.step.x = scene.player.pos.x + (scene.player.dir.x );
	scene.minimap.step.y = scene.player.pos.y + (scene.player.dir.y );
	if (scene.minimap.step.x < 0)
		scene.minimap.step.x = 0;
	else if (scene.minimap.step.x > scene.map.rows)
		scene.minimap.step.x = scene.map.rows;
	if (scene.minimap.step.y < 0)
		scene.minimap.step.y = 0;
	else if (scene.minimap.step.y > scene.map.cols)
		scene.minimap.step.y = scene.map.cols;
	// i got the rotation of the minimap and the movement into the cells
	printf("image -> {%u} {%u}\n", image->width , image->height);
	// printf("step -> {%f} {%f}\n",scene.minimap.step.x, scene.minimap.step.y);
	// printf("scale -> {%f} {%f}\n",scene.minimap.scale.x, scene.minimap.scale.y);
	draw_minimap(image, scene, scene.minimap.pos, scene.minimap.radius,
		0xFFFFFFFF);
	draw_player(image, scene.minimap.pos, scene.minimap.radius >> 4,
		0x0000FFFF);
}
