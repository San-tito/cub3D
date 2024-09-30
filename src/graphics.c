/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/30 19:59:51 by santito          ###   ########.fr       */
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

int	get_pixel(mlx_texture_t *texture, unsigned int x, unsigned int y)
{
	int	r;
	int	g;
	int	b;
	int	color;

	color = *(unsigned *)(texture->pixels + ((x + y * texture->width)
				* sizeof(int)));
	r = get_green(color);
	g = get_blue(color);
	b = color & 0xFF;
	return (get_color(b, g, r, (color >> 24) & 0xFF));
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

void	draw_wall(mlx_image_t *image, unsigned int x, t_wall wall, t_cell state)
{
	int		y;
	int		pixel;
	double	step;
	double	tex_pos;

	y = wall.start;
	step = 1.0 * wall.texture->height / wall.height;
	tex_pos = (wall.start - image->height / 2 + wall.height / 2) * step;
	while (y <= wall.end)
	{
		wall.tex.y = (int)tex_pos & (wall.texture->height - 1);
		tex_pos += step;
		pixel = get_pixel(wall.texture, wall.tex.x, wall.tex.y);
		if (state == DOOR_CLOSING || DOOR_OPENING == state)
			pixel = (pixel >> 1) & get_color(0x64, 0x64, 0x64, 0xFF);
		put_pixel(image, x, y, pixel);
		y++;
	}
}
