/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/22 20:00:34 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(mlx_image_t *image, unsigned int x, unsigned int y,
		unsigned int color)
{
	int				i;
	unsigned char	*pixel;

	if (x < (*image).width && y < (*image).height)
	{
		pixel = (*image).pixels + (y * (*image).width + x) * sizeof(int);
		i = sizeof(int) * 6;
		while (i >= 0)
		{
			*pixel++ = (color >> i) & 0xFF;
			i -= sizeof(int) * 2;
		}
	}
}

void	draw_ceiling(mlx_image_t *image, int draw_start, uint32_t color, int x)
{
	unsigned int	y;

	y = 0;
	while (y <= (unsigned)draw_start && y < image->height)
	{
		put_pixel(image, x, y, color);
		y++;
	}
}

void	draw_floor(mlx_image_t *image, int draw_end, uint32_t color, int x)
{
	unsigned int	y;

	y = draw_end;
	while (y < image->height - 1)
	{
		put_pixel(image, x, y, color);
		y++;
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
