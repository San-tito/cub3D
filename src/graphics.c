/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/22 18:32:46 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_updown(mlx_image_t *image, t_scene scene)
{
	t_ivec	ceil;

	ceil.x = 0;
	ceil.y = 0;
	while (ceil.y <= (int32_t)(image->height / 2))
	{
		ceil.x = 0;
		while (ceil.x <= (int32_t)image->width)
			put_pixel(image, ceil.x++, ceil.y, scene.ceiling_color);
		ceil.y++;
	}
	while (ceil.y <= (int32_t)(image->height - 1))
	{
		ceil.x = 0;
		while (ceil.x <= (int32_t)image->width)
			put_pixel(image, ceil.x++, ceil.y, scene.floor_color);
		ceil.y++;
	}
}

void	put_pixel(mlx_image_t *image, unsigned int x, unsigned int y,
		unsigned int color)
{
	unsigned char	*pixel;

	if (x < (*image).width && y < (*image).height)
	{
		pixel = (*image).pixels + (y * (*image).width + x) * sizeof(int);
		*(pixel++) = (uint8_t)(color >> 24);
		*(pixel++) = (uint8_t)(color >> 16);
		*(pixel++) = (uint8_t)(color >> 8);
		*(pixel++) = (uint8_t)(color & 0xFF);
	}
}

void	game_loop(void *param)
{
	t_core		*core;
	mlx_image_t	*image;

	core = (t_core *)param;
	image = core->img;
	event_listener(core->mlx, &core->scene);
	mouse_listener(core->mlx, &core->scene);
	if (core->scene.refresh)
	{
		ft_bzero((*image).pixels, (*image).width * (*image).height
			* sizeof(int));
		draw_updown(image, core->scene);
		raycast(image, core->scene);
		minimap(image, core->scene);
		core->scene.refresh = 0;
	}
}

void	start_renderer(t_core core)
{
	mlx_loop_hook(core.mlx, game_loop, &core);
	mlx_close_hook(core.mlx, (void (*)(void *))mlx_close_window, core.mlx);
	mlx_loop(core.mlx);
}
