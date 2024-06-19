/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:14:08 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/19 21:53:11 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map
{
	char	**data;
}			t_map;

t_map		load_map(int argc, char **argv);

/* *************** */
/*       MAP       */
/* *************** */
# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

#endif /* MAP_H */
