/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/08/07 19:53:34 by deordone         ###   ########.fr       */
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

static void draw_square(mlx_image_t *img, t_vec2 begin, unsigned int size, double color)
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
	t_vec2 sex;

	sex.y = image->height / 2;
	sex.x = image->width / 2;
	map_pos.y = 0;
	map_pos.x = 0;
	while(map_pos.y <= 12)
	{
		map_pos.x = 0;
		while (map_pos.x <= 31)
		{
			if (scene.map.cells[map_pos.y][map_pos.x] == '1')
			{
				draw_square(image, sex, 22,0xFFFFFFFF);
				sex.x += 2;
			}
			map_pos.x++;
		}
		map_pos.y++;
	}
}

static void draw_player2D(mlx_image_t *image, t_scene scene)
{
	unsigned int size;

	size = 25;
	draw_square(image, scene.player.cor, size, 0xFF00FFFF);
}

void	rasterise(mlx_image_t *image, t_scene scene)
{
	(void)image;
	//(void)scene;

	//cast_pos(image, scene);
	draw_player2D(image, scene);
	draw_map2D(image, scene);
	// draw_line(image, v0, v1, 0xFFFFFF);
	// mlx_put_pixel(image, image->width / 2, image->height / 2, );
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
	core.scene.player.cor.x = core.img->width / 2;
	core.scene.player.cor.y = core.img->height / 2;
	mlx_loop_hook(core.mlx, game_loop, &core);
	mlx_close_hook(core.mlx, (void (*)(void *))mlx_close_window, core.mlx);
	mlx_loop(core.mlx);
}
