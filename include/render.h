/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:30:16 by droied            #+#    #+#             */
/*   Updated: 2024/10/09 10:24:50 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

void	put_pixel(mlx_image_t *image, unsigned int x, unsigned int y,
			unsigned int color);
int		get_pixel(uint8_t *pixels, uint32_t width, unsigned int x,
			unsigned int y);
void	draw_wall(mlx_image_t *image, unsigned int x, t_wall wall,
			t_cell state);
void	draw_ceiling(mlx_image_t *image, int draw_start, uint32_t color, int x);
void	draw_floor(mlx_image_t *image, int draw_end, uint32_t color, int x);

#endif /* RENDER_H */
