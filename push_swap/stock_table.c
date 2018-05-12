/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyildiz- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 19:08:22 by jyildiz-          #+#    #+#             */
/*   Updated: 2018/05/12 08:43:09 by jyildiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
int		first_elem(long *pile, int nb)
{
	int i;

	i = 0;
	while (i < nb && pile[i] == NONE)
		i++;
	return (i);
}
*/
void	free_pile(t_env *env);
{
	env->a ? free(a) : 0;
	env->b ? free(b) : 0;
}
