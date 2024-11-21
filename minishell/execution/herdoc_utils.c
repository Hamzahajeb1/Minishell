#include "minishell.h"

void	write_expanded_line(t_data *sh, t_redirect *redirct, int fd[2], char *p)
{
	char	*expand;

	find_head(sh, p, &expand); // to do
	write(fd[1], expand, ft_strlen(expand));
	write(fd[1], "\n", 1);
	free(expand);
}

void	write_unexpanded_line(int fd[2], char *p)
{
	write(fd[1], p, ft_strlen(p));
	write(fd[1], "\n", 1);
}

void	heredoc_line(t_data *sh, t_redirect *redirct, int fd[2], char *p)
{
	if (redirct->token == HERDOC)
		write_expanded_line(sh, redirct, fd, p);
	else
		write_unexpanded_line(fd, p);
}


void    herdoc_err(int fd[2], char *p)
{
    ft_putstr_fd("minishell: ",STDERR_FILENO);
	ft_putstr_fd(HERDOC_ERR, STDERR_FILENO);
	close(fd[1]);
	free(p);
	exit(0);
}


void    handler(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        exit (1);
    }
}