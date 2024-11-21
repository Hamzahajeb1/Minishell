#include "libft.h"

static	int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

long long	ft_atoi_2(const char *str)
{
	int					i;
	unsigned long long	nb;
	int					sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		nb = (nb * 10) + str[i++] - 48;
		if (nb >= LLONG_MAX && sign == 1)
			return (-1);
		else if (nb >= LLONG_MAX && sign == -1)
			return (0);
	}
	return ((int)(nb * sign));
}
// to fix