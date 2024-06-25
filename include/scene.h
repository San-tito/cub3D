/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by droied            #+#    #+#             */
/*   Updated: 2024/06/25 14:20:46 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef enum e_orient
{
	NORTH = 'N',
	EAST = 'E',
	SOUTH = 'S',
	WEST = 'W'
}				t_orient;

typedef enum e_zone
{
	SPACE = '0',
	WALL = '1',
	DOOR = 'D'
}				t_zone;


typedef struct s_player
{
	void *pos; /* Player's position */
	t_orient	spawn_orient;
}				t_player;

/* ****************** */
/*       PLAYER       */
/* ****************** */
# define PLAYERSPEED 3000
# define RUNSPEED 6000

typedef struct s_map
{
	t_zone		**zone;
	int			maxHeight;
	int			maxWidth;
}				t_map;

t_map			load_map(int argc, char **argv);

#endif /* SCENE_H */
