/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyildiz- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:46:44 by jyildiz-          #+#    #+#             */
/*   Updated: 2018/02/15 18:55:06 by jyildiz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			ft_lgt(t_arg *tmp, int nbchar, t_buf **buf)
{
	int	i;

	i = 0;
	while (i < tmp->precision - nbchar)
	{
		ft_strnconcat(buf, "0", 1);
		i++;
	}
}

static void			ft_wdth(t_arg *tmp, t_buf **buf, int nbc, intmax_t nb)
{
	int		i;
	int		nbchar;

	i = 0;
	if (tmp->precision < nbc)
		nbchar = nbc;
	else
		nbchar = tmp->precision;
	if (tmp->plus == 1 || tmp->space == 1)
		nbchar++;
	if (nb == 0 && tmp->precision == 0)
		nbchar = 0;
	while (i < tmp->width - nbchar)
	{
		if (tmp->zero == 0)
			ft_strnconcat(buf, " ", 1);
		else
			ft_strnconcat(buf, "0", 1);
		i++;
	}
}

static uintmax_t	ft_con(t_arg *tmp, t_buf **buf)
{
	if (tmp->tab[0] == 'l' && tmp->tab[1] == 'l')
		return (va_arg((*buf)->va, unsigned long long));
	else if (tmp->tab[0] == 'h' && tmp->tab[1] == 'h')
		return ((unsigned char)va_arg((*buf)->va, unsigned int));
	else if (tmp->tab[0] == 'h')
		return ((unsigned short int)va_arg((*buf)->va, unsigned int));
	else if (tmp->tab[0] == 'l')
		return (va_arg((*buf)->va, unsigned long));
	else if (tmp->tab[0] == 'z')
		return (va_arg((*buf)->va, size_t));
	else if (tmp->tab[0] == 'j')
		return (va_arg((*buf)->va, uintmax_t));
	else
		return (va_arg((*buf)->va, unsigned int));
}

void				ft_conv_u(t_arg *tmp, t_buf **buf)
{
	char		*str;
	uintmax_t	nb;

	nb = ft_con(tmp, buf);
	str = ft_itoa_base(nb, 10, 1);
	if (tmp->minus == 1)
	{
		ft_lgt(tmp, ft_strlen(str), buf);
		if (nb != 0 || tmp->precision != 0)
			ft_strnconcat(buf, str, ft_strlen(str));
		ft_wdth(tmp, buf, ft_strlen(str), nb);
	}
	else
	{
		ft_wdth(tmp, buf, ft_strlen(str), nb);
		ft_lgt(tmp, ft_strlen(str), buf);
		if (nb != 0 || tmp->precision != 0)
			ft_strnconcat(buf, str, ft_strlen(str));
	}
	free(str);
}
