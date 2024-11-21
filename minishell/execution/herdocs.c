#include "minishell.h"

void	update_exit_status_on_error(t_data *sh, int flg)
{
	if ( 0 != WEXITSTATUS(flg) && WIFEXITED(flg))
	{
		sh->herdoc_err = 1;
		sh->ext_status = 130;
	}
}

void	herdoc_parent_process(t_data *sh, t_comnd *comnd, int fd[2])
{
	int	flg;

	close(fd[1]);
	comnd->in_fd = fd[0];
	waitpid(sh->pid, &flg, 0);
	update_exit_status_on_error(sh, flg);
}

void	herdoc_child_process(t_data *sh, t_redirect *redirct, int fd[2])
{
	char	*p;

	close(fd[0]);
	signal(SIGINT, handler);
	while (1)
	{
		p = readline("> ");
		if (p == NULL)
			herdoc_err(fd, p);
		if (0 == ft_strcmp(p, redirct->name))
		{
			free(p);
			close(fd[1]);
			exit(0);
		}
		heredoc_line(sh, redirct, fd, p);
		free(p);
	}
}

void	herdoc_limiter(t_redirect *redirct)
{
    t_redirect  *tmp;
	int         i;

    i = 0;
    tmp = redirct;
	while (tmp)
	{
		if (tmp->token == HERDOC || tmp->token == HERDOC_EXP)
			i++;
		tmp = tmp->next;
	}
	if (16 < i)
	{
		ft_putstr_fd("minishell: maximum here-document count exceeded\n", STDERR_FILENO);
		exit(2);
	}
}

void    process_herdoc(t_data *sh, t_comnd *comnd, t_redirect *redirct)
{
    int fd[2];

    if (sh->herdoc_err)
        return;
    if (-1 == pipe(fd))
    {
        perror("pipe");
        sh->cmd->redirct_err = -1;
        return ;
    }
    herdoc_limiter(redirct);
    sh->pid = fork();
    if (-1 == sh->pid)
    {
        perror("fork");
        sh->cmd->redirct_err = -1;
        return ;
    }
    if (sh->pid == 0)
        herdoc_child_process(sh, redirct, fd);
    else
        herdoc_parent_process(sh, comnd, fd);
}