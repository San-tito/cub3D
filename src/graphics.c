/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/13 17:50:02 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_updown(mlx_image_t *image, t_scene scene)
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

void put_pixel(mlx_image_t *image, int x, int y, int color)
{
    int i;
    unsigned char *pixel;

    if ((unsigned)x < (*image).width && (unsigned)y < (*image).height)
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
		core->scene.refresh = 0;
	}
}

void	start_renderer(t_core core)
{
	mlx_loop_hook(core.mlx, game_loop, &core);
	// mlx_cursor_hook(core.mlx, mouse_listener, &core);
	mlx_close_hook(core.mlx, (void (*)(void *))mlx_close_window, core.mlx);
	mlx_loop(core.mlx);
}
