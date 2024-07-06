/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:11 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/06 02:19:10 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_core	core;

	/* setup argc and argc to scene */
	core.scene = create_scene(argc, argv);
	/* setup MLX; create window; setup width, heitht, image */
	// setup mlx ((void *)core.mlx, (void *)core.image);
	/* setup callback */
	// callback setup(core.mlx, core.scene);
	/* rasterize in image */
	// rendering(core.image, core.scene);
	// separation of concerns  
	rendering_setup(core);
	mlx_terminate(core.mlx);
	return (EXIT_SUCCESS);
}
