/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droied <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:23:37 by droied            #+#    #+#             */
/*   Updated: 2024/09/13 17:47:49 by droied           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALLBACK_H
# define CALLBACK_H

void	rotate(t_scene *scene, double angle);
void	mouse_listener(mlx_t *, t_scene *);
void	event_listener(mlx_t *, t_scene *);

#endif /* CALLBACK_H */
