/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:10:49 by sguzman           #+#    #+#             */
/*   Updated: 2024/06/19 21:37:14 by sguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_player
{
	void *pos; /* Player's position */
	void *dir; /* Direction vector the player is facing */
}	t_player;

/* ****************** */
/*       PLAYER       */
/* ****************** */
# define PLAYERSPEED 3000
# define RUNSPEED 6000

#endif /* PLAYER_H */