/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deordone <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:14:59 by deordone          #+#    #+#             */
/*   Updated: 2024/10/10 18:27:39 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_animation(mlx_image_t *img, t_animation *a, char *tex_path)
{
	a->tex = mlx_load_png(tex_path);
	if (!a->tex)
		return ;
	a->type = DEFAULT;
	a->total_frames.x = SPRITE_FRAMES_X;
	a->total_frames.y = SPRITE_FRAMES_Y;
	a->sprite.x = a->tex->width / a->total_frames.x;
	a->sprite.y = a->tex->height / a->total_frames.y;
	a->pos.x = (img->width) - a->sprite.x;
	a->pos.y = (img->height) - a->sprite.y;
	a->slice.x = a->sprite.x;
	a->slice.y = a->sprite.y;
	a->current_frame.x = 0;
	a->current_frame.y = 0;
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
			color = get_pixel(a->tex->pixels, a->tex->width, x, y);
			if (get_alpha(color) != 0)
				put_pixel(img, (a->pos.x - a->slice.x) + x, (a->pos.y
						- a->slice.y) + y, color);
			x++;
		}
		y++;
	}
}

static void	animator(mlx_image_t *img, t_animation *a, t_ivec frame)
{
	if (a->type == DEFAULT)
	{
		if (a->current_frame.x == 4 && a->current_frame.y == 0)
		{
			a->current_frame.x = 5;
			a->current_frame.y = 2;
		}
	}
	if (a->type == INTERACT)
	{
		if (a->current_frame.x == 2 && a->current_frame.y == 2)
			a->type = DEFAULT;
	}
	draw_frame(img, a, frame);
}

void	animation(mlx_image_t *img, t_animation *a)
{
	if (a->tex == 0)
		return ;
	if (a->current_frame.x < a->total_frames.x)
		a->current_frame.x++;
	if (a->current_frame.y < a->total_frames.y
		&& a->current_frame.x == a->total_frames.x)
		a->current_frame.y++;
	if (a->current_frame.x == a->total_frames.x)
		a->current_frame.x = 0;
	if (a->current_frame.y == a->total_frames.y)
		a->current_frame.y = 0;
	animator(img, a, a->current_frame);
}
