#include "minishell.h"

void handle_pipe(t_data *sh, int *fd, int *flg)
{
    fd[0] = -1;
    fd[1] = -1;
    if (-1 == sh->cmd->next && pipe(fd))
    {
        perror("pipe");
        *flg = 1;
    }
}

void	child_process(t_data *sh, int fd[2])
{
	init_input(sh);
	init_output(sh, fd);
	signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	if (-1 == sh->cmd->redirct_err)
		exit(1);
	if (1 == sh->cmd->dup)
	{
		sh->cmd->dup = 0;
		exit(1);
	}
	if (if_builtins(*sh))
		exe_builtins(sh);
	else
		execut(sh);
	exit(sh->ext_status);
}

void handle_fork(t_data *sh, int *fd)
{
    sh->pid = fork();
    
    if (0 == sh->pid)
        child_process(sh, fd);
    else
    {
        if (3 <= fd[1])
            close(fd[1]);
        if (3 <= sh->fd[0])
            close(sh->fd[0]);
        sh->fd[0] = fd[0];
    }
}

void multi_comnd(t_data *sh, int *flg)
{
    int fd[2];

    *flg = 0;
    handle_pipe(sh, fd, flg);
    if (*flg == 0)
        handle_fork(sh, fd);
}
