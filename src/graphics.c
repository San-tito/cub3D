/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/06 19:00:26 by droied           ###   ########.fr       */
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
void	rasterise(mlx_image_t *image, t_scene scene)
{
	t_vec2 v0;
	t_vec2 v1;
	(void)scene;

	v0.x = image->width/2;
	v0.y = image->height/2;
	v1.x = image->width;
	v1.y = image->height;
	draw_line(image, v0, v1);
	mlx_put_pixel(image, image->width/2, image->height/2, 0xFFFFFF);	
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
