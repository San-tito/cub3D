/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:23:37 by droied            #+#    #+#             */
/*   Updated: 2024/09/28 18:53:54 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALLBACK_H
# define CALLBACK_H

# include "scene.h"

void	rotate(t_scene *scene, double angle);
void	mouse_listener(mlx_t *mlx, t_scene *scene);
void	event_listener(mlx_t *mlx, t_scene *scene);

#endif /* CALLBACK_H */
