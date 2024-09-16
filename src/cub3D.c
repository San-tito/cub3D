/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:11 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/15 20:22:26 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "print.h"

void	begin_window(t_core *core, int32_t width, int32_t height)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(width, height, PROGRAM, 0);
	if (mlx == 0)
		libx_error("mlx error");
	mlx_set_mouse_pos(mlx, width >> 1, height >> 1);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_size(mlx, width, height);
	mlx_set_mouse_pos(mlx, width / 2, height << 1);
	mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	mlx_set_window_pos(mlx, 0, 0);
	image = mlx_new_image(mlx, width, height);
	if (image == 0 || (mlx_image_to_window(mlx, image, 0, 0)) < 0)
		libx_error("mlx error");
	core->mlx = mlx;
	core->img = image;
}

int	main(int argc, char **argv)
{
	t_core	core;

	core = (t_core){};
	core.scene = create_scene(argc, argv);
	print_scene(&core.scene);
	begin_window(&core, 1280, 960);
	start_renderer(core);
	dispose_scene(&core.scene);
	dispose_mlx(core.mlx);
	return (EXIT_SUCCESS);
}
