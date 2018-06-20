/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-rent <pde-rent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:26:09 by pde-rent          #+#    #+#             */
/*   Updated: 2018/06/20 18:26:10 by pde-rent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	put_room_links(t_env *env, t_room *room)
{
	t_link *l;

	l = room->link;
	(room && &(room->id[0])) ? 0 : put_error(env, "Error: No room to target");
	l ? 0 : put_error(env, "Error: Room has no link");
	while ((l && l->prev && l->prev->room))
		(l = l->prev);
	pstr(2, "linked to room ", '\0');
	pstr(2, room->id, '\0');
	pstr(2, ":\n", '\0');
	&(l->room->id[0]) ? pstr(2, &(l->room->id[0]), '\n') : 0;
	while (l->next)
	{
		l = l->next;
		&(l->room->id[0]) ? pstr(2, &(l->room->id[0]), '\n') : 0;
	}
}

void	free_room_links(t_env *env, t_room *room)
{
	t_link *l;

	l = room->link;
	room ? 0 : put_error(env, "Error: No room to target");
	l ? 0 : put_error(env, "Error: Room has no link");
	while ((l && l->prev && l->prev->room))
		(l = l->prev);
	while (l->next)
	{
		l = l->next;
		l->prev ? free(l->prev) : 0;
	}
	l ? free(l) : 0;
}
