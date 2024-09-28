/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:11 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/28 15:33:34 by santito          ###   ########.fr       */
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
	mlx_set_window_pos(mlx, 0, 0);
	image = mlx_new_image(mlx, width, height);
	if (image == 0 || (mlx_image_to_window(mlx, image, 0, 0)) < 0)
		libx_error("mlx error");
	core->mlx = mlx;
	core->img = image;
}

void	game_loop(void *param)
{
	t_core		*core;
	mlx_image_t	*image;
	static int	frame_count = 0;

	core = (t_core *)param;
	image = core->img;
	event_listener(core->mlx, &core->scene);
	mouse_listener(core->mlx, &core->scene);
	update_doors(&core->scene.map, frame_count);
	if (core->scene.refresh)
	{
		ft_bzero((*image).pixels, (*image).width * (*image).height
			* sizeof(int));
		raycast(image, core->scene, frame_count);
		minimap(image, core->scene);
		core->scene.refresh = 0;
	}
	frame_count++;
}

int	main(int argc, char **argv)
{
	t_core	core;

	core = (t_core){};
	core.scene = create_scene(argc, argv);
	print_scene(&core.scene);
	begin_window(&core, 1280, 960);
	mlx_loop_hook(core.mlx, game_loop, &core);
	mlx_close_hook(core.mlx, (void (*)(void *))mlx_close_window, core.mlx);
	mlx_loop(core.mlx);
	dispose_scene(&core.scene);
	dispose_mlx(core.mlx);
	return (EXIT_SUCCESS);
}
