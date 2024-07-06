/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:30:16 by droied            #+#    #+#             */
/*   Updated: 2024/07/06 18:54:14 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

void    start_renderer(t_core core);
void	draw_line(mlx_image_t *image, t_vec2 v0, t_vec2 v1);

#endif /* RENDER_H */
