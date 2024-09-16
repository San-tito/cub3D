/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 18:52:02 by droied            #+#    #+#             */
/*   Updated: 2024/09/14 17:50:17 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3D.h"

typedef struct s_minimap
{
	t_ivec		pos;
	uint32_t	radius;
}				t_minimap;

void	minimap(mlx_image_t *image, t_scene scene);

#endif /* MINIMAP_H */
