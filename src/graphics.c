/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/08/19 12:41:53 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	rasterise(mlx_image_t *image, t_scene scene)
{
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
