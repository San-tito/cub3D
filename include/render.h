/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:30:16 by droied            #+#    #+#             */
/*   Updated: 2024/09/23 09:32:52 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

void	put_pixel(mlx_image_t *, unsigned int, unsigned int, unsigned int);
int		get_pixel(mlx_texture_t *texture, unsigned int x, unsigned int y);
void	draw_wall(mlx_image_t *, unsigned int, t_wall);
void	draw_ceiling(mlx_image_t *, int, uint32_t, int);
void	draw_floor(mlx_image_t *, int, uint32_t, int);

#endif /* RENDER_H */
