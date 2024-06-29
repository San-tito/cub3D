/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/29 17:34:39 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


static t_core *init_minimap(t_core *core)
{
	t_minimap min_map;

	min_map.m.x = MINI_M_X;
	min_map.m.y = MINI_M_Y;
	min_map.p.a = 0;
	min_map.p.x = min_map.m.x;
	min_map.p.y = min_map.m.y;
	min_map.p.dx = cos(deg2rad(min_map.p.a)) * 5;
	min_map.p.dy = sin(deg2rad(min_map.p.a)) * 5;
	core->scene.minimap = min_map;
	return (core);
}




void	rendering_setup(t_core core)
{
	core.mlx = mlx_init(WIDTH, HEIGHT, PROGRAM, 1);
	if (core.mlx == 0)
		libx_error("mlx error");
	core.img = mlx_new_image(core.mlx, WIDTH, HEIGHT);
	if (core.img == 0)
		libx_error("mlx error");
	init_minimap(&core);
	draw_minimap(core);
	mlx_loop_hook(core.mlx, ft_hook, &core);
	mlx_loop(core.mlx);
}
