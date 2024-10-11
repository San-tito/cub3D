/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/10/11 13:09:45 by deordone         ###   ########.fr       */
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

int	get_pixel(uint8_t *pixels, uint32_t width, unsigned int x, unsigned int y)
{
	int	a;
	int	color;

	color = *(unsigned *)(pixels + ((x + y * width) * sizeof(int)));
	a = (color & 0xFF);
	return (get_color(a, get_blue(color), get_green(color), get_red(color)));
}

void	draw_ceiling(mlx_image_t *image, int draw_start, uint32_t color, int x)
{
	unsigned int	y;
	uint32_t		new_color;
	t_dcolor		c;
	t_dcolor		s;

	(void)draw_start;
	c.r = get_red(color);
	c.g = get_green(color);
	c.b = get_blue(color);
	s.r = c.r / (float)(image->height >> 1);
	s.g = c.g / (float)(image->height >> 1);
	s.b = c.b / (float)(image->height >> 1);
	y = 0;
	while (y < image->height)
	{
		new_color = ((unsigned char)(c.r - (s.r
						* y)) << 24) | ((unsigned char)(c.g - (s.g
						* y)) << 16) | ((unsigned char)(c.b - (s.b
						* y)) << 8) | (color & 0xFF);
		put_pixel(image, x, y, new_color);
		y++;
	}
}

void	draw_floor(mlx_image_t *image, int draw_end, uint32_t color, int x)
{
	unsigned int	y;

	y = draw_end;
	while (y < image->height)
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
		pixel = get_pixel(wall.texture->pixels, wall.texture->width, wall.tex.x,
				wall.tex.y);
		if (state == DOOR_CLOSING || DOOR_OPENING == state)
			pixel = (pixel >> 1) & get_color(0x64, 0x64, 0x64, 0xFF);
		put_pixel(image, x, y, pixel);
		y++;
	}
}
