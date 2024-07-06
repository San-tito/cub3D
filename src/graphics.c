/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/06 11:19:30 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_core *init_minimap(t_core *core)
{
	t_minimap min_map;

	min_map.m.x = ft_div(core->scene.width, 12);
	min_map.m.y = ft_div(core->scene.height, 7);
	min_map.p.a = 0;
	min_map.p.x = min_map.m.x;
	min_map.p.y = min_map.m.y;
	min_map.p.dx = cos(deg2rad(min_map.p.a)) * 5;
	min_map.p.dy = sin(deg2rad(min_map.p.a)) * 5;
	min_map.size = div2(ft_div(core->scene.width, 8));
	core->scene.minimap = min_map;
	draw_minimap(core);
	return (core);
}

void	rendering_setup(t_core core)
{
	core.mlx = mlx_init(1, 1, PROGRAM, 1);
	if (core.mlx == 0)
		libx_error("mlx error");
	mlx_get_monitor_size(0, &core.scene.width, &core.scene.height);
	mlx_set_window_size(core.mlx, core.scene.width, core.scene.height);
	init_minimap(&core);
	mlx_loop_hook(core.mlx, ft_hook, &core);
	mlx_loop(core.mlx);
}
