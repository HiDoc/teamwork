/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyildiz- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:29:14 by jyildiz-          #+#    #+#             */
/*   Updated: 2018/05/14 17:00:47 by jyildiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		sort_pile(t_env *env)
{
	if (ext_sort(env) && all_sort(env))
		return (1);
	return (0);
}

int		ext_sort(t_env *env)
{
	while (A_TOP > A_BOT)

}