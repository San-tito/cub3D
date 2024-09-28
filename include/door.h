/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:46:40 by sguzman           #+#    #+#             */
/*   Updated: 2024/09/28 15:33:26 by santito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

# include "cub3D.h"

void	place_doors(t_map *);
void	interact_with_door(t_map *, t_fvec, t_fvec);
void	update_doors(t_map *, int);

#endif /* DOOR_H */
