/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/08/09 00:57:02 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_core	*init_minimap(t_core *core)
{
	/*	t_minimap min_map;
		min_map.m.x = ft_div(core->scene.width, 12);
		min_map.m.y = ft_div(core->scene.height, 7);
		min_map.p.a = 0;
		min_map.p.x = min_map.m.x;
		min_map.p.y = min_map.m.y;
		min_map.p.dx = cos(deg2rad(min_map.p.a)) * 5;
		min_map.p.dy = sin(deg2rad(min_map.p.a)) * 5;
		min_map.size = div2(ft_div(core->scene.width, 8));
		core->scene.minimap = min_map;
		draw_minimap(core);*/
	(void)core;
	return (core);
}
/*
static void cast_north( t_scene scene )
{
	t_vec2 caster;

	caster.x = scene.player.pos.x;
	caster.y = scene.player.pos.y - 1;
	while (caster.y >= 0 && scene.map.cells[caster.y][caster.x] == '0')
    {
		caster.y--;
	}
	ft_printf("Wall found in coord [%d] [%d] \n", caster.x, caster.y);
}


static void cast_west( t_scene scene )
{
	t_vec2 caster;

	caster.x = scene.player.pos.x - 1;
	caster.y = scene.player.pos.y;
	while (caster.x >= 0 && scene.map.cells[caster.y][caster.x] == '0')
    {
		caster.x--;
	}
	ft_printf("Wall found in coord [%d] [%d] \n", caster.x, caster.y);
}


static void cast_east( t_scene scene )
{
	t_vec2 caster;

	caster.x = scene.player.pos.x + 1;
	caster.y = scene.player.pos.y;
	while (caster.x >= 0 && scene.map.cells[caster.y][caster.x] == '0')
    {
		caster.x++;
	}
	ft_printf("Wall found in coord [%d] [%d] \n", caster.x, caster.y);
}


static void cast_south( t_scene scene )
{
	t_vec2 caster;

	caster.x = scene.player.pos.x;
	caster.y = scene.player.pos.y + 1;
	while (caster.y >= 0 && scene.map.cells[caster.y][caster.x] == '0')
    {
		caster.y++;
	}
	ft_printf("Wall found in coord [%d] [%d] \n", caster.x, caster.y);
}

static void cast_pos(mlx_image_t *image, t_scene scene)
{
	(void)image;
	t_funori	orientation[] = { &cast_north, &cast_west, &cast_east, &cast_south};
	t_orient	ori[4] = { NORTH, WEST, EAST, SOUTH};
	unsigned int i;

	i = 0;
	while (i < 4 && ori[i] != scene.player.spawn_orient)
		i++;
	if (i < 4)
		(orientation[i])(scene);
}*/

static void	image_clear(mlx_image_t *image)
{
	unsigned int x;
	unsigned int y;

	y = 0;
	x = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
			mlx_put_pixel(image, x++, y, 0x000000FF);
		y++;
	}
}

static void draw_square(mlx_image_t *img, t_vec3 begin, unsigned int size, double color)
{
	unsigned int x;
	unsigned int y;

	x = begin.x;
	y = begin.y;
	while (y <= (begin.y + size))
	{
		x = begin.x;
		while (x <= (begin.x + size))
			mlx_put_pixel(img, x++, y, color);
		y++;
	}
}

static void draw_map2D(mlx_image_t *image, t_scene scene)
{
	t_vec2 map_pos;
	t_vec3 sex;

	sex.y = image->height / 2;
	sex.x = image->width / 2;
	map_pos.y = 0;
	map_pos.x = 0;
	while(map_pos.y <= 13)
	{
		map_pos.x = 0;
		sex.y += 42;
	sex.x = image->width / 2;
		while (map_pos.x <= 32)
		{
			if (scene.map.cells[map_pos.y][map_pos.x] == '1')
			{
				draw_square(image, sex, 42,0xFFFFFFFF);
			}
			sex.x += 42;
			map_pos.x++;
		}
		map_pos.y++;
	}
}

static void draw_player2D(mlx_image_t *image, t_scene scene)
{
	unsigned int size;

	size = 25;
	draw_square(image, scene.player.p, size, 0xFF00FFFF);
	/*if (scene.player.p.a < 0)
		scene.player.p.a += 2 * PI;
	else if (scene.player.p.a > 2 * PI)
		scene.player.p.a -= 2 * PI;*/
	scene.player.p.dx = cos(scene.player.p.a) * 5; 
	scene.player.p.dy = sin(scene.player.p.a) * 5;
	t_vec2 beg;
	t_vec2 end;

	beg.x = scene.player.p.x + (size / 2); 
	beg.y = scene.player.p.y + (size / 2);
	end.x = beg.x + scene.player.p.dx * 5;
	end.y = beg.y + scene.player.p.dy * 5;
	draw_line(image, beg, end, 0xFF00FFFF);
}

static void raycast(mlx_image_t *image, t_scene scene)
{
	unsigned int i = 0;
	t_vec3 m;
	t_vec3 r;
	float atan;

	r.a = scene.player.p.a;
	while (i < 1)
	{
		m.dx = 0;
		atan = -1 / tan(r.a);
		if (r.a > PI)
		{
			r.y = ((scene.player.p.y>>6)<<6) -0.0001;
			r.x = (scene.player.p.y - r.y) * atan + scene.player.p.x;
			r.dy = -64;
			r.dx = -r.dy * atan;
		}
		else if (r.a < PI)
		{
			r.y = ((scene.player.p.y>>6)<<6) + 64;
			r.x = (scene.player.p.y - r.y) * atan + scene.player.p.x;
			r.dy = 64;
			r.dx = -r.dy * atan;
		}
		else 
		{
			r.x = scene.player.p.x;
			r.y = scene.player.p.y;
			m.dx = 8;
		}
		while (m.dx < 8)
		{
			m.x = r.x >> 6;
			m.y = r.y >> 6;
			m.dy = m.y * !!!mapx + m.x;
			if (m.dy < !!!mapx*!!mapy && !!map[m.dy] == 1)
				m.dx = 8;
			else 
			{
				r.x += r.dx;
				r.y += r.dy;
				m.dx += 1;
			}
		}
		i++;
	}
	//si esto compila solo haria falta dibujar
}

void	rasterise(mlx_image_t *image, t_scene scene)
{
	//(void)image;
	//(void)scene;

	//cast_pos(image, scene);
	draw_player2D(image, scene);
	draw_map2D(image, scene);
	raycast(image, scene);
}

void	game_loop(void *param)
{
	t_core	*core;

	core = (t_core *)param;
	event_listener(core->mlx, &core->scene);
	if (core->scene.refresh)
	{
		image_clear(core->img);
		rasterise(core->img, core->scene);
		core->scene.refresh = 0;
	}
}

void	start_renderer(t_core core)
{
	mlx_loop_hook(core.mlx, game_loop, &core);
	mlx_close_hook(core.mlx, (void (*)(void *))mlx_close_window, core.mlx);
	mlx_loop(core.mlx);
}
