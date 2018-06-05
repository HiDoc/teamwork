/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyildiz- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:04:20 by jyildiz-          #+#    #+#             */
/*   Updated: 2018/06/05 18:10:06 by jyildiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_all(t_env *env)
{
	plong(1, env->nb_ants, '\n');
	print_rooms(env);
	print_link(env);
}

void	print_room(t_env *env)
{
	t_room *r;

	r = env->parsed_room;
	if (r)
	{
		pstr(1, &(r->id), ' ');
		plong(1, r->x, ' ');
		plong(1, r->y, '\n');
		while(r->next)
		{
			r = r->next;
			pstr(1, &(r->id), ' ');
			plong(1, r->x, ' ');
			plong(1, r->y, '\n');
		}
	}
}

void	print_link(t_env *env)
{
	t_link *l;

	l = env->parsed_link;
	if (l & l->next)
	{
		pstr(1, &(l->linked_room->id), '-');
		pstr(1, &(l->next->linked_room->id), '\n');
		while(l->next->next && l->next->next->next)
		{
			l = l->next->next;
			pstr(1, &(l->linked_room->id), '-');
			pstr(1, &(l->next->linked_room->id), '\n');
		}
	}
}