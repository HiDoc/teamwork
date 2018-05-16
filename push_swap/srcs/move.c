/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyildiz- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 20:01:50 by jyildiz-          #+#    #+#             */
/*   Updated: 2018/05/15 15:18:20 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	*swap(t_env *env, char which)
{
	long	*pile;
	int		tmp;
	int		i;

	pile = (which == 'A' ? env->a : env->b);
	i = (which == 'A' ? env->a1 : env->b1);
	if (i < env->size && pile[i] != NONE && pile[i + 1] != NONE)
	{
		tmp = pile[i];
		pile[i] = pile[i + 1];
		pile[i + 1] = tmp;
	}
	archive_move(env, "S", which, env->this_move);
	return (pile);
}

t_env	*push(t_env *env, char to)
{
	int		*i;
	int		*j;
	long	*pilefrom;
	long	*pileto;

	pilefrom = (to == 'B' ? env->a : env->b);
	pileto = (to == 'B' ? env->b : env->a);
	i = (to == 'B' ? &env->a1 : &env->b1);
	j = (to == 'B' ? &env->b1 : &env->a1);
	if (pilefrom[*i] != NONE)
	{
		(*j == env->size - 1 && pileto[*j] == NONE) ? 0 : --*j;
		pileto[*j] = pilefrom[*i];
		pilefrom[*i] = NONE;
		*i == env->size - 1 ? 0 : ++*i;
	}
	archive_move(env, "P", to, env->this_move);
	return (env);
}

long	*rotate(t_env *env, char which)
{
	long	*pile;
	int		tmp;
	int		i;

	pile = (which == 'A' ? env->a : env->b);
	i = (which == 'A' ? env->a1 : env->b1);
	if (i < env->size)
	{
		tmp = pile[i];
		while (i < env->size - 1)
		{
			pile[i] = pile[i + 1];
			i++;
		}
		pile[i] = tmp;
	}
	archive_move(env, "R", which, env->this_move);
	return (pile);
}

long	*reverse_rotate(t_env *env, char which)
{
	long	*pile;
	int		tmp;
	int		felem;
	int		i;

	pile = (which == 'A' ? env->a : env->b);
	felem = (which == 'A' ? env->a1 : env->b1);
	i = env->size - 1;
	if (pile[env->size - 1] != NONE)
	{
		tmp = pile[env->size - 1];
		while (i >= felem)
		{
			pile[i] = pile[i - 1];
			i--;
		}
		pile[felem] = tmp;
	}
	archive_move(env, "RR", which, env->this_move);
	return (pile);
}

void	combine(long (*move)(t_env *, char), t_env *env)
{
	move(env, 'A');
	move(env, 'B');
}
