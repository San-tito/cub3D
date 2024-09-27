/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/23 09:31:52 by santito          ###   ########.fr       */
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
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	return (b << 24 | g << 16 | r << 8 | ((color >> 24) & 0xFF));
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

void	draw_wall(mlx_image_t *image, unsigned int x, t_wall wall)
{
	int		y;
	double	step;
	double	tex_pos;

	y = wall.start;
	step = 1.0 * wall.texture->height / wall.height;
	tex_pos = (wall.start - image->height / 2 + wall.height / 2) * step;
	while (y <= wall.end)
	{
		wall.tex.y = (int)tex_pos & (wall.texture->height - 1);
		tex_pos += step;
		put_pixel(image, x, y, get_pixel(wall.texture, wall.tex.x, wall.tex.y));
		y++;
	}
}
