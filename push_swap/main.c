/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyildiz- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:26:08 by jyildiz-          #+#    #+#             */
/*   Updated: 2018/05/13 19:37:31 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_error(t_env *env, const char *err_msg)
{
	free_piles(env);
	pstr(err_msg);
	exit(1);
}

int		alloc_piles(t_env *env)
{
	int i;

	i = -1;
	if (!(env->a = (int *)malloc(sizeof(int) * env->size))
		|| !(env->b = (int *)malloc(sizeof(int) * env->size)))
		put_error(env, "Error");
	while (++i < env->size)
	{
		env->a[i] = NONE;
		env->b[i] = NONE;
	}
	return (1);
}

void	free_piles(t_env *env);
{
	env->a ? free(a) : 0;
	env->b ? free(b) : 0;
}

int 	arg_to_piles(t_env *env, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac && av[i])
		env->size += space_in(av[i]);
	alloc_piles(env);
	i = 0;
	while (++i < ac && av[i])
		space_in(av[i]) ? split_to_pile(env, av[i], space_in(av[i])) : push_to_pile(env, av[i]);
	return (1);
}

inline	void init_piles(t_env *env, int ac)
{
	env->size = ac;
	env->a = NULL;
	env->b = NULL;
}

inline	void deinit_piles(t_env *env, int ac)
{
	free_piles()
}

int		main(int ac, char **av)
{
	t_env env;

	init_env(&env, ac);
	if (ac < 2 || !av[1] || !compliant_arg(ac, av, &env))
		put_error(env, Error);
	arg_to_piles()
	sort_pile(&env);
	deinit_env(&env);
	return (1);
}
