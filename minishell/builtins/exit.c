#include "minishell.h"

int	is_num(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (0);
}

int	putinfd(char *data)
{
	ft_putstr_fd("minishell : exit :", STDERR_FILENO);
	ft_putstr_fd(data, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	t_secnd.ext_status = 2;
	return (0);
}

int		ext_arg(char *data, long long *i)
{
	*i = ft_atoi_2(data);
	if (*i == LLONG_MAX || *i == LLONG_MIN || !is_num(data))
		putinfd(data);
	return (1);
}

void	ft_exit(char **argv)
{
	long long	i;
	
	t_secnd.ext_status = 0;
	if (!t_secnd.pipe)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (argv[1])
	{
		if (!ext_arg(argv[1], &i))
			exit(0);
		t_secnd.ext_status = (i % 256 + 256) % 256;
		if (argv[2])
		{
			ft_putstr_fd("exit : too many arguments\n", STDERR_FILENO);
			t_secnd.ext_status = 1;
			exit(1);
		}
	}
	exit(t_secnd.ext_status);
}
