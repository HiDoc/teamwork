#include "lem_in.h"

int			spaces_in(const char *str)
{
	const char	*p = str;
	int			i;
	int			prev;

	prev = 1;
	i = 0;
	while (*p)
	{
		(is_space(*p) && !prev) ? i++ : 0;
		prev = is_space(*p) ? 1 : 0;
		p++;
	}
	return (prev ? (i - 1) : i);
}

int			is_int(char *av)
{
	return (av && (ft_atol(av) >= -2147483648 && ft_atol(av) <= 2147483647));
}
