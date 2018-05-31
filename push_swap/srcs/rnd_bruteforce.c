/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_bruteforce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:13:50 by fmadura           #+#    #+#             */
/*   Updated: 2018/05/29 14:08:26 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		ipow(int a, int power)
{
	int ret;

	ret = 1;
	while (power > 0)
	{
		if (power & 1)
			ret *= a;
		a *= a;
		power >>= 1;
	}
	return (ret);
}

static int		jack(t_env *env, char which, long *pile, int max_depth)
{
	long	tmp_pile[env->size];
	int		rnd_mv;
	int		prev_mv;
	int		moved;
	int		nb_mv;
	int		shuffle;
	int		start;

	start = which == 'a' ? env->a1 : env->b1;
	srand(time(NULL));
	duplicate_pile(pile, tmp_pile, start, env->size - 1);
	nb_mv = 0;
	while (++nb_mv <= max_depth)
	{
		shuffle = 0;
		while (++shuffle <= ipow(3, nb_mv))
		{
			prev_mv = 0;
			moved = 0;
			while(moved < nb_mv)
			{
				rnd_mv = (1 + (rand() / (RAND_MAX / 3)));
				(rnd_mv == 1 && prev_mv != 1 && ++moved) ? swap(env, which) : 0;
				(rnd_mv == 2 && prev_mv != 3 && ++moved) ? rotate(env, which) : 0;
				(rnd_mv == 3 && prev_mv != 2 && ++moved) ? reverse_rotate(env, which) : 0;
				prev_mv = rnd_mv;
			}
			//put_moves(env->first_move, 1, ' ');
			if ((which == 'a' && is_sort(pile, start, env->size - 1))
				|| (which == 'b' && is_rev_sort(pile, start, env->size - 1))){
				//dprintf(2, "\r>> SUCCESS!! <<\n");	
				return (1);
			}
			//dprintf(2, "\rfail #%d!", shuffle);
			del_moves(env);
			duplicate_pile(tmp_pile, pile, start, env->size - 1);
		}
	}
	return (0);
}

void			median_bruteforce(t_env *env, char which)
{
	int		max_mv;
	long	pivot;
	long	*pile;
	
	pile = env->b;
	(which == 'a') ? pile = env->a : 0;
	max_mv = ((which == 'a' ? LEN_A : LEN_B) * 3) / 2;

	pivot = (LEN_A % 2) ? env->mean : (env->mean - 1);
	while (MIN_A <= pivot)
	{
		while (A1 > pivot)
			ra_or_rra(env, pivot) == 1 ? RA : RRA;
		PB;
	}
	dprintf(2, "after median sort:\n");
	put_piles(env);
	jack(env, 'a', env->a, max_mv);
	jack(env, 'b', env->b, max_mv);
	while (B1 != NONE)
		PA;
	optimize(env);
	dprintf(2, "after bruteforce:\n");
	put_piles(env);
}

void			bruteforce(t_env *env, char which)
{
	int		max_mv;
	long	*pile;

	pile = env->b;
	(which == 'a') ? pile = env->a : 0;
	max_mv = ((which == 'a' ? LEN_A : LEN_B) * 3);
	jack(env, which, pile, max_mv);
}