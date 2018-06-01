/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piles_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyildiz- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:25:31 by jyildiz-          #+#    #+#             */
/*   Updated: 2018/05/18 10:58:04 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		is_sort(long *pile, int start, int end)
{
	int		i;

	i = start - 1;
	while (++i < end)
		if (pile[i] >= pile[i + 1])
			return (0);
	return (1);
}

int		is_rev_sort(long *pile, int start, int end)
{
	int		i;

	i = end + 1;
	while (--i > start)
		if (pile[i] >= pile[i - 1])
			return (0);
	return (1);
}

int		all_sort(t_env *env)
{
	if (!is_sort(env->a, 0, env->size - 1) || env->b[env->size - 1] != NONE)
		return (0);
	return (1);
}

double	mean_value(long *pile, int start, int end)
{
	int		i;
	int		sum;

	i = start - 1;
	sum = 0;
	if (end - start > 2)
		while (++i <= end)
			sum += pile[i];
	return ((end - start > 2) ? (double)sum / (double)(i - start) : 0);
}

int		put_unindexed_piles(t_env *env)
{
	int		i;

	i = env->a1 - 1;
	while (++i < env->size)
		env->a[i] = env->c[(int)env->a[i]];
	put_piles(env);
	return (1);
}