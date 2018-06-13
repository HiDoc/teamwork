#include "lem_in.h"

int			scmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

int			pstr(int fd, const char *s, char end)
{
	char *p;

	p = (char *)s;
	*s ? write(fd, s, slen(p)) : 0;
	return (write(fd, &end, 1) ? 1 : 0);
}

int			plong(int fd, long n, char end)
{
	char	str[16];
	int		i;

	n < 0 ? write(fd, "-", 1) : 0;
	n = (n < 0 ? -n : n);
	i = 15;
	str[i--] = '\0';
	n == 0 ? str[--i] = '0' : 0;
	while (n != 0 && (str[--i] = '0' + (n % 10)))
		n /= 10;
	while (i > 0)
		str[--i] = '\0';
	write(fd, &str, 15);
	write(fd, &end, 1);
	return (1);
}

int			scat(char *dest, const char *src, const char c)
{
	int i;

	//dprintf(2, "src: %s dest: %s\n", src, dest);
	i = -1;
	while (src[++i] != '\0')
		dest[i] = src[i];
	dest[i] = c;
	//dprintf(2, "slen: %d i: %d\n", slen((char *)src), i);
	dest[++i] = '\0';
	return (1);
}

long		fatol(t_env *env, const char *str)
{
	long		nb;
	long		sign;

	while (*str && is_space(*str))
		++str;
	(*str) ? 0 : put_error(env, "Error: fatol: nothing to parse");
	sign = *str == '-' ? -1 : 1;
	if (*str == '+' || *str == '-')
		++str;
	nb = 0;
	while (*str && is_digit(*str))
		nb = 10 * nb + (*(str++) - '0');
	while (*str && is_space(*str))
		++str;
	(*str && nb == 0) ? put_error(env, "Error: expected a number") : 0;
	(nb > 2147483647 || nb < -2147483647)
	? put_error(env, "Error: expected an integer") : 0;
	return (nb * sign);
}
