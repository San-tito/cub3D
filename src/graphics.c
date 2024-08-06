/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/08/06 20:40:26 by deordone         ###   ########.fr       */
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
}

void	rasterise(mlx_image_t *image, t_scene scene)
{
	(void)image;
	(void)scene;
	cast_pos(image, scene);
//	raycast
	// draw_line(image, v0, v1, 0xFFFFFF);
	// mlx_put_pixel(image, image->width / 2, image->height / 2, );
}

void	game_loop(void *param)
{
	t_core	*core;

	core = (t_core *)param;
	event_listener(core->mlx, core->scene);
	if (core->scene.refresh)
	{
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
