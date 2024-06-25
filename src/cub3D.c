/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:43:11 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/25 15:31:49 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	terminate(t_core core)
{
	mlx_terminate(core.mlx);
}

int	main(int argc, char **argv)
{
	t_core	core;

	core.scene = create_scene(argc, argv);
	rendering_setup(core);
	terminate(core);
	return (EXIT_SUCCESS);
}
