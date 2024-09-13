/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/13 09:23:42 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
static void	image_clear(mlx_image_t *image)
{
	unsigned int	x;
	unsigned int	y;

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
*/

static void	draw_updown(mlx_image_t *image, t_scene scene)
{
	t_ivec	ceil;

	ceil.x = 0;
	ceil.y = 0;
	while (ceil.y <= (int32_t)(image->height / 2))
	{
		ceil.x = 0;
		while (ceil.x <= (int32_t)image->width)
			mlx_put_pixel(image, ceil.x++, ceil.y, scene.ceiling_color);
		ceil.y++;
	}
	while (ceil.y <= (int32_t)(image->height - 1))
	{
		ceil.x = 0;
		while (ceil.x <= (int32_t)image->width)
			mlx_put_pixel(image, ceil.x++, ceil.y, scene.floor_color);
		ceil.y++;
	}
}

void	rasterise(mlx_image_t *image, t_scene scene)
{
	draw_updown(image, scene);
	raycast(image, scene);
}

void	game_loop(void *param)
{
	t_core		*core;
	mlx_image_t	*image;

	core = (t_core *)param;
	image = core->img;
	event_listener(core->mlx, &core->scene);
	//if (core->scene.refresh)
	//{
		ft_bzero((*image).pixels, (*image).width * (*image).height
			* sizeof(int));
		rasterise(core->img, core->scene);
		// core->scene.refresh = 0;
	// }
}

void	start_renderer(t_core core)
{
	mlx_loop_hook(core.mlx, game_loop, &core);
	mlx_close_hook(core.mlx, (void (*)(void *))mlx_close_window, core.mlx);
	mlx_loop(core.mlx);
}
