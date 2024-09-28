/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/28 18:47:35 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPOSE_H
# define DISPOSE_H

# include "scene.h"

void	dispose_map(t_map *map);
void	dispose_mlx(mlx_t *mlx);
void	dispose_scene(t_scene *scene);

#endif /* DISPOSE_H */
