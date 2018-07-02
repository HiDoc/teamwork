/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:37:38 by fmadura           #+#    #+#             */
/*   Updated: 2018/07/02 21:30:13 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <strings.h>

int		ft_asm(char **argv)
{
	int		fd;
	t_iter	*iter;
	t_ops	*ops;

	iter = iter_new();
	if (iter == NULL)
		return (1);
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd > 0)
		{
			iter = lexer(iter, fd);
			ops = parser(iter, fd, 0);
			iter->header.prog_size = ops_get_len(ops);
			ops_get_lab(iter, ops);
			write_all("test.cor", ops, iter->header);
			iter_del(iter);
			ops_del(ops);
		}
		close(fd);
	}
	return (0);
}
