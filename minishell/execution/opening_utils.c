#include "minishell.h"

void    handle_error(t_data *sh, t_redirect *redirct, t_comnd *comnd)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(redirct->name, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	comnd->redirct_err = -1;
	sh->ext_status = EXIT_FAILURE;
	return ;
}

void    in_redirect(t_data *sh, t_redirect *redirct, t_comnd *comnd)
{
    if (-1 == access(redirct->name, F_OK))
        handle_error(sh, redirct, comnd);
}