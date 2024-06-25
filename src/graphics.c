/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:01:04 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/26 00:47:30 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rendering_setup(t_core core)
{
	core.mlx = mlx_init(WIDTH, HEIGHT, PROGRAM, 1);
	if (core.mlx == 0)
		libx_error("mlx error");
	core.img = mlx_new_image(core.mlx, WIDTH, HEIGHT);
	if (core.img == 0)
		libx_error("mlx error");
	draw_minimap(core);
	mlx_loop_hook(core.mlx, ft_hook, core.mlx);
	mlx_loop(core.mlx);
}
