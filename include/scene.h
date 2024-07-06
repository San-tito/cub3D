/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by droied            #+#    #+#             */
/*   Updated: 2024/07/06 10:47:46 by deordone         ###   ########.fr       */
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
}					t_orient;

typedef struct s_vec3
{
	float x;
	float y;
	float dx;
	float dy;
	float a;
}			t_vec3;

typedef struct s_vec
{
	float x;
	float y;
}			t_vec;

typedef enum e_zone
{
	SPACE = '0',
	WALL = '1',
	DOOR = 'D'
}					t_zone;

typedef struct s_player
{
	void *pos; /* Player's position */
	t_orient		spawn_orient;
}					t_player;

/* ****************** */
/*       PLAYER       */
/* ****************** */

# define PLAYERSPEED 3000
# define RUNSPEED 6000

typedef struct s_map
{
	t_zone			**zone;
	int				height;
	int				width;
}					t_map;

typedef struct s_minimap
{
	uint32_t	size;
	t_vec		m;
	t_vec3		p;
}				t_minimap;

typedef struct s_assets
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*prueba;
}					t_assets;

typedef struct s_scene
{
	t_map			map;
	t_player		player;
	t_minimap		minimap;
	t_assets		assets;
	int32_t			width;
	int32_t			height;
	int				floor_color;
	int				roof_color;
}					t_scene;

t_scene			create_scene(int argc, char **argv);

#endif /* SCENE_H */
