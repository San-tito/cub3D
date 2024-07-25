/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by droied            #+#    #+#             */
/*   Updated: 2024/07/06 18:52:37 by droied           ###   ########.fr       */
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
	float			x;
	float			y;
	float			dx;
	float			dy;
	float			a;
}					t_vec3;

typedef struct s_vec2
{
	int32_t			x;
	int32_t			y;
}					t_vec2;

typedef enum e_tile
{
	SPACE = '0',
	WALL = '1',
	DOOR = 'D'
}					t_tile;

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
	t_tile			**tiles;
	int				height;
	int				width;
}					t_map;

typedef struct s_minimap
{
	uint32_t		size;
	t_vec2			map;
	t_vec3			player;
}					t_minimap;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
}					t_textures;

typedef struct s_scene
{
	t_map			map;
	t_player		player;
	t_textures		textures;
	int				refresh;
	int				floor_color;
	int				roof_color;
}					t_scene;

t_scene				create_scene(int, char **);

#endif /* SCENE_H */
