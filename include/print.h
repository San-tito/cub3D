/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/08/20 14:43:39 by deordone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "scene.h"

void	print_map(const t_map *map);
void	print_ray(const t_ray *ray);
void	print_player(const t_player *player);
void	print_textures(const t_textures *textures);
void	print_scene(const t_scene *scene);

#endif /* PRINT_H */
