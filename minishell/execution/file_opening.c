#include "minishell.h"

void    ft_print_err(t_data *sh, t_redirect *redirct, t_comnd *comnd)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(redirct->name, STDERR_FILENO);
    perror(" ");
    comnd->redirct_err = -1;
    sh->ext_status = EXIT_FAILURE;
    return ;
}

void file_opening(t_data *sh, t_redirect *redirct, t_comnd *comnd)
{
    int fd;

    fd = -1;
    if (0 == ft_strcmp(redirct->name, ""))
        return;
    if (redirct->token == REDIC_IN)
        fd = open(redirct->name, O_RDONLY);
    else if (redirct->token == REDIC_OUT)
        fd = open(redirct->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (redirct->token == APND_OUT)
        fd = open(redirct->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1)
        ft_print_err(sh, redirct, comnd);
    if (redirct->token == REDIC_IN)
        comnd->in_fd = fd;
    else
        comnd->out_fd = fd;
}

void    handle_redirects(t_data *sh, t_redirect *redirect, t_comnd *comnd)
{
    if (redirect->token != HERDOC_EXP && redirect->token != HERDOC)
    {
        file_opening(sh, redirect, comnd);

        if (-1 == comnd->redirct_err)
            return;
    }
}

void    in_out_redirect(t_data *sh, t_comnd *comnd)
{
    t_redirect *tmp; 
    
    tmp = comnd->redirect;
    while (tmp)
    {
        if (tmp->token == REDIC_IN)
        {
            in_redirect(sh, tmp, comnd);
            if (-1 == comnd->redirct_err)
                return ;
        }
        else
        {
            handle_redirects(sh, tmp, comnd);
            if (-1 == comnd->redirct_err)
                return ;
        }
        tmp = tmp->next;
    }
}


void    open_redirect(t_data *sh)
{
    t_comnd *tmp;
    
    tmp = sh->cmd;
    while (tmp)
    {
        in_out_redirect(sh, tmp);
        tmp = tmp->next;
    }
}