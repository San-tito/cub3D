/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:11 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/30 09:22:29 by deordone         ###   ########.fr       */
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
	// mlx_get_monitor_size(0, &width, &height);
	// mlx_set_window_size(mlx, width, height);
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
		raycast(image, core->scene);
		minimap(image, core->scene);
		core->scene.refresh = 0;
	}
	frame_count++;
}

static void	init_minimap(t_scene *scene, mlx_image_t *image)
{
	scene->minimap.pos.x = (image->width >> 4);
	scene->minimap.pos.y = (image->height >> 3);
	scene->minimap.radius = (scene->minimap.pos.x + scene->minimap.pos.y) / 1.5;
	scene->minimap.player.x = scene->minimap.pos.x + scene->minimap.radius;
	scene->minimap.player.y = scene->minimap.pos.y + scene->minimap.radius;
	scene->minimap.scale.x = (float)(scene->map.cols)
		/ (scene->minimap.radius << 1) / 3.0;
	scene->minimap.scale.y = (float)(scene->map.rows)
		/ (scene->minimap.radius << 1) / 3.0;
	scene->minimap.color = (((-scene->ceiling_color >> 24) & 0xFF) << 24 | ((-scene->ceiling_color >> 16) & 0xFF) << 16 | ((-scene->ceiling_color >> 8) & 0xFF) << 8 | 0xFF);
}
int	main(int argc, char **argv)
{
	t_core	core;

	core = (t_core){};
	core.scene = create_scene(argc, argv);
	print_scene(&core.scene);
	begin_window(&core, 1280, 960);
	init_minimap(&core.scene, core.img);
	mlx_loop_hook(core.mlx, game_loop, &core);
	mlx_close_hook(core.mlx, (void (*)(void *))mlx_close_window, core.mlx);
	mlx_loop(core.mlx);
	dispose_scene(&core.scene);
	dispose_mlx(core.mlx);
	return (EXIT_SUCCESS);
}
