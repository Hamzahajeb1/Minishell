#include "minishell.h"

void	print_args(char **argv, int newline, int fd)
{
	int	i;
	
	i = 0;
	while(argv[i])
	{
		ft_putstr_fd(argv[i], fd);
		if (argv[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (i == 0 || newline)
		ft_putstr_fd("\n", fd);
}

int	check_flg(char *str)
{
	int	i;
	
	i = 0;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	process(char **argv, int fd)
{
	int	i;
	int flg;
	
	flg = 1;
	i = 0;
	while(argv[i] && check_flg(argv[i]))
	{
		flg = 0;
		i++;
	}
	print_args(&argv[i], flg, fd);
}

void	ft_echo(t_data *sh)
{
	int	fd;
	
	fd = sh->cmd->out_fd;
	if (sh->cmd->argv[1] == NULL)
		ft_putstr_fd("\n", fd);
	else if (sh->cmd->argv[1][0] == '-')
		process(sh->cmd->argv, fd);
	else
		print_args(sh->cmd->argv + 1, 1, fd);
}
