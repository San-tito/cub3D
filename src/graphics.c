/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/06 04:08:58 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_core *init_minimap(t_core *core)
{
	t_minimap min_map;

	min_map.m.x = ft_div(div2(core->scene.width), 6);
	min_map.m.y = ft_div(div2(core->scene.height), 4);
	min_map.p.a = 0;
	min_map.p.x = min_map.m.x;
	min_map.p.y = min_map.m.y;
	min_map.p.dx = cos(deg2rad(min_map.p.a)) * 5;
	min_map.p.dy = sin(deg2rad(min_map.p.a)) * 5;
	min_map.size = ft_div(div2(core->scene.height), 6);
	core->scene.minimap = min_map;
	return (core);
}

void	rendering_setup(t_core core)
{
	core.mlx = mlx_init(1, 1, PROGRAM, 1);
	if (core.mlx == 0)
		libx_error("mlx error");
	mlx_get_monitor_size(0, &core.scene.width, &core.scene.height);
	mlx_set_window_size(core.mlx, core.scene.width, core.scene.height);
	dprintf(2, "width %d\n", core.scene.width);
	dprintf(2, "height %d\n", core.scene.height);
	core.img = mlx_new_image(core.mlx, core.scene.width, core.scene.height);
	if (core.img == 0)
		libx_error("mlx error");
	init_minimap(&core);
	draw_minimap(core);
	mlx_loop_hook(core.mlx, ft_hook, &core);
	mlx_loop(core.mlx);
}
