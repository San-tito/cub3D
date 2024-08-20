/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:18:44 by sguzman           #+#    #+#             */
/*   Updated: 2024/08/20 10:28:13 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void set_player(t_player *player)
{
	player->rotate = 0;
	player->spawn_orient = 0;
	player->pos.x = 0.0;
	player->pos.y = 0.0;
	player->dir.x = 0.0;
	player->dir.y = 0.0;
	player->plane.x = 0.0;
	player->plane.y = 0.0;
	player->move.x = 0;
	player->move.y = 0;
}
