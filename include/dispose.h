/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:48 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/15 20:21:26 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPOSE_H
# define DISPOSE_H

# include "scene.h"

void	dispose_map(t_map *);
void	dispose_mlx(mlx_t *);
void	dispose_scene(t_scene *);


#endif /* DISPOSE_H */
