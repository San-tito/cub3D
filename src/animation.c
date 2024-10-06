/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:14:59 by deordone          #+#    #+#             */
/*   Updated: 2024/10/06 02:25:29 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_animation(mlx_image_t *img, t_animation *a, char *tex_path)
{
	a->tex = mlx_load_png(tex_path);
	if (!a->tex)
		exit(42);
	a->total_frames.x = 5;
	a->total_frames.y = 3;
	a->sprite.x = a->tex->width / a->total_frames.x;
	a->sprite.y = a->tex->height / a->total_frames.y;
	a->pos.x = (img->width >> 1);
	a->pos.y = (img->height) - a->sprite.y;
	a->slice.x = a->sprite.x;
	a->slice.y = a->sprite.y;
	a->current_frame.x = 0;
	a->current_frame.y = 0;
	a->motion = 1;
}

void	draw_frame(mlx_image_t *img, t_animation *a, t_ivec s)
{
	int32_t	x;
	int32_t	y;
	int32_t	color;

	a->slice.x = a->sprite.x * s.x;
	a->slice.y = a->sprite.y * s.y;
	y = a->slice.y;
	while (y < (int32_t)(a->sprite.y) + a->slice.y)
	{
		x = a->slice.x;
		while (x < (int32_t)(a->sprite.x) + a->slice.x)
		{
			color = get_pixel(a->tex, x, y);
			if (get_alpha(color) != 0)
				put_pixel(img, (a->pos.x - a->slice.x) + x, (a->pos.y
						- a->slice.y) + y, color);
			x++;
		}
		y++;
	}
}

void	animation(mlx_image_t *img, t_animation *a, int8_t *motion)
{
	if (*motion == a->total_frames.x * a->total_frames.y)
	{
		a->current_frame.x = 0;
		a->current_frame.y = 0;
		return ;
	}
	if (a->current_frame.x < a->total_frames.x)
		a->current_frame.x++;
	if (a->current_frame.y < a->total_frames.y
		&& a->current_frame.x == a->total_frames.x)
		a->current_frame.y++;
	if (a->current_frame.x == a->total_frames.x)
		a->current_frame.x = 0;
	if (a->current_frame.y == a->total_frames.y)
		a->current_frame.y = 0;
	draw_frame(img, a, a->current_frame);
}
