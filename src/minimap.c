/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:46:40 by droied            #+#    #+#             */
/*   Updated: 2024/09/17 10:48:59 by droied           ###   ########.fr       */
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
	t_fvec	m;
	t_ivec	pos;
	// t_ivec  aux;

	m.y = 0;
	// aux = aux_minimap(img, c, radius);
	pos.y = scene.player.pos.y;
	while (pos.y < radius << 1 && pos.y + c.y < (int32_t)img->height)
	{
		m.x = 0;
		pos.x = scene.player.pos.x;
		//pos.x = scene.player.pos.x;
		while (pos.x < radius << 1 && pos.x + c.x < (int32_t)img->width)
		{
			if (((pos.x - radius) * (pos.x - radius)) + ((pos.y - radius)
					* (pos.y - radius)) < (radius * radius))
			{
				if (scene.map.cells[(int)m.y][(int)m.x] == SPACE)
					put_pixel(img, pos.y + c.y, pos.x + c.x, color);
			}
			pos.x++;
		if (pos.x % 10 == 0 && m.x < scene.map.cols - 1)
			 { 
				m.x++;
				// printf("m.x %i\n", (int)m.x);
			}
		}
		pos.y++;
		if (pos.y % 10 == 0 && m.y < scene.map.rows - 1)
		{
			m.y++;
			// printf("m.y %i\n", (int)m.y);
		}
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
	scene.minimap.step.x = scene.player.pos.x + (scene.player.dir.x * 5);
	scene.minimap.step.y = scene.player.pos.y + (scene.player.dir.y * 5);
	if (scene.minimap.step.x < 0)
		scene.minimap.step.x = 0;
	else if (scene.minimap.step.x > scene.map.rows)
		scene.minimap.step.x = scene.map.rows;
	if (scene.minimap.step.y < 0)
		scene.minimap.step.y = 0;
	else if (scene.minimap.step.y > scene.map.cols)
		scene.minimap.step.y = scene.map.cols;
	// i got the rotation of the minimap and the movement into the cells
	printf("step -> {%i} {%i}\n",scene.minimap.step.x, scene.minimap.step.y);
	draw_minimap(image, scene, scene.minimap.pos, scene.minimap.radius,
		0xFFFFFFFF);
	draw_player(image, scene.minimap.pos, scene.minimap.radius >> 4,
		0x0000FFFF);
}
