/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:30:16 by droied            #+#    #+#             */
/*   Updated: 2024/09/13 14:54:34 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

void	put_pixel(mlx_image_t *, int, int, int);
void	start_renderer(t_core);
void	draw_line(mlx_image_t *, t_fvec, t_fvec, int);

#endif /* RENDER_H */
