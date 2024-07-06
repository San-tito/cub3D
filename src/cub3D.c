/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:11 by sguzman           #+#    #+#             */
/*   Updated: 2024/07/06 17:30:19 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	event_listener(t_core *core)
{
	keyhook(core);	
	//ft_mousehook(core);
}

void	begin_window(t_core *core)
{
	mlx_t *mlx;
	mlx_image_t *image;

	mlx = mlx_init(1, 1, PROGRAM, 0);
	if (mlx == 0)
		libx_error("mlx error");
	mlx_set_setting(MLX_FULLSCREEN, 1);
	mlx_get_monitor_size(0, &mlx->width, &mlx->height);
	mlx_set_window_size(mlx, mlx->width, mlx->height);
	image = mlx_new_image(mlx, mlx->width, mlx->height);
	if (image == 0)
		libx_error("mlx error");
	core->mlx = mlx;
	core->img = image;
}

int	main(int argc, char **argv)
{
	t_core	core;

	/* setup argc and argc to scene */
	core.scene = create_scene(argc, argv);
	/* setup MLX; create window; setup width, heitht, image */
	begin_window(&core);
	/* setup callback */
	event_listener(&core);
	/* rasterize in image */
	//rendering(core.image, core.scene);
	// separation of concerns  
	rendering_setup(core);
	mlx_terminate(core.mlx);
	return (EXIT_SUCCESS);
}
