/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:29:18 by droied            #+#    #+#             */
/*   Updated: 2024/10/09 10:37:42 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "cub3D.h"

typedef enum e_orient
{
	NORTH = 'N',
	EAST = 'E',
	SOUTH = 'S',
	WEST = 'W'
}					t_orient;

typedef enum e_type
{
	INTERACT,
	MOVE,
	ROTATE_RIGHT,
	ROTATE_LEFT,
	DEFAULT
}					t_type;

typedef struct s_dcolor
{
	double			r;
	double			g;
	double			b;
}					t_dcolor;

typedef struct s_icolor
{
	uint32_t		r;
	uint32_t		g;
	uint32_t		b;
}					t_icolor;

typedef struct s_fvec
{
	double			x;
	double			y;
}					t_fvec;

typedef struct s_ivec
{
	int32_t			x;
	int32_t			y;
}					t_ivec;

typedef enum e_cell
{
	SPACE = '0',
	WALL,
	DOOR_CLOSING,
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN
}					t_cell;

typedef struct s_player
{
	t_fvec			pos;
	t_fvec			plane;
	t_fvec			dir;
	t_orient		spawn_orient;
}					t_player;

typedef struct s_map
{
	t_cell			**cells;
	int32_t			rows;
	int32_t			cols;
}					t_map;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*door;
}					t_textures;

typedef struct s_animation
{
	mlx_texture_t	*tex;
	t_type			type;
	t_ivec			pos;
	t_ivec			max;
	t_ivec			sprite;
	t_ivec			slice;
	t_ivec			total_frames;
	t_ivec			current_frame;
}					t_animation;

typedef struct s_minimap
{
	t_ivec			pos;
	t_ivec			player;
	t_fvec			step;
	t_fvec			scale;
	uint32_t		radius;
	int32_t			color;
}					t_minimap;

typedef struct s_scene
{
	t_map			map;
	t_player		player;
	t_textures		textures;
	t_minimap		minimap;
	t_animation		a;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
}					t_scene;

t_scene				create_scene(int argc, char **argv);
void				minimap(mlx_image_t *image, t_scene scene);
void				place_doors(t_map *map);
void				interact_with_door(t_map *map, t_fvec player_pos,
						t_fvec player_dir);
void				update_doors(t_map *map, int frame_count);
void				init_animation(mlx_image_t *img, t_animation *a,
						char *tex_path);
void				animation(mlx_image_t *img, t_animation *a);
void				draw_frame(mlx_image_t *img, t_animation *a, t_ivec s);

#endif /* SCENE_H */
