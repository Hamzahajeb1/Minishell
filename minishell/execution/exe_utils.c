#include "minishell.h"

void	execute_child_process(t_data *sh)
{
	signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	if (2 < sh->cmd->in_fd)
		dup_in(sh); // to do
	if (sh->cmd->out_fd != STDOUT_FILENO)
		dup_out(sh, 0); // to do
	execut(sh);
	exit(EXIT_SUCCESS);
}

int if_builtins(t_data sh)
{
    int     count;
    char    *str1;
    char    **str2;
    
    count = 0;
    str1 = BUILTINS;
    if (!sh.cmd || !sh.cmd->argv || !sh.cmd->argv[0])
        return(1);
    str2 = ft_split(str1, ' ');
    if (!str2)
        return (1);
    while (str2[count])
    {
        if (0 == ft_strcmp(sh.cmd->argv[0], str2[count]))
            return (0);
        count++;
    }
    return (1);
}

void	sngl_comnd(t_data *sh, int *flg)
{
	if (0 == if_builtins(*sh))
		to_builtins(sh, flg);
	else
	{
		sh->pid = fork();
		if (-1 == sh->pid)
		{
			perror("fork");
			*flg = 1;
			return;
		}
		else if (0 == sh->pid)
			execute_child_process(sh);
	}
}

void    invalid_redirect(t_data *sh, t_comnd *comnd, t_redirect *redirct)
{
    if (0 == ft_strcmp(redirct->name, ""))
    {
        ft_putstr_fd("minishell: ", STDERR_FILENO);
	    ft_putstr_fd(redirct->name, STDERR_FILENO);
	    ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	    comnd->redirct_err = -1;
	    sh->ext_status = 1;
	    return ;
    }
}