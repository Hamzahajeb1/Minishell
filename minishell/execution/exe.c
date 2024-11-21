#include "minishell.h"

void    handle_comnd(t_data *sh)
{
    t_comnd *tmp;
    
    tmp = sh->cmd;
    while(tmp)
    {
        tmp->out_fd = 1;
        tmp->in_fd = 0;
        tmp->dup = 0;
        tmp->redirct_err = 0;
        tmp = tmp->next;
    }
}

void    herdocs_process(t_data *sh)
{
    t_redirect  *tmp_redirect;
    t_comnd     *tmp_comnd;
    
    tmp_comnd = sh->cmd;
    tmp_redirect = tmp_comnd->herdocs;
    while (tmp_comnd != NULL)
    {
        while (tmp_redirect != NULL)
        {
            process_herdoc(sh, tmp_comnd, tmp_redirect);
            tmp_redirect = tmp_redirect->next;
        }
        tmp_comnd = tmp_comnd->next;
    }
}

void    if_redirect_valid(t_data *sh)
{
    t_redirect  *tmp_redirect;
    t_comnd     *tmp_comnd;
    
    tmp_comnd = sh->cmd;
    tmp_redirect = tmp_comnd->redirect;
    while (tmp_comnd)
    {
        if (tmp_comnd->token = AMBG)
        {
            sh->cmd->redirct_err = 1;
            sh->cmd->dup = 1;
            sh->ext_status = EXIT_FAILURE;
            ft_putstr_fd("minishell : ambiguous redirect\n", STDERR_FILENO);
            return ;
        }
        while (tmp_redirect)
        {
            invalid_redirect(sh, tmp_comnd, tmp_redirect);
            if (1 == tmp_comnd->dup)
                break ;
            tmp_redirect = tmp_redirect->next;
        }
        tmp_comnd = tmp_comnd->next;
    }
}

void    exe_initialize(t_data *sh, int *flg)
{
    if (1 == sh->size)
    {
        if (0 == sh->cmd->redirct_err)
            sngl_comnd(sh, flg);
    }
    else
    {
        while (sh->cmd)
        {
            multi_comnd(sh, flg);
            sh->cmd = sh->cmd->next;
        }
    }
}

void    exe(t_data *sh)
{
    int flg;
    
    handle_comnd(sh);
    herdocs_process(sh);
    if (sh->herdoc_err)
        return ;
    if_redirect_valid(sh);
    if (1 != sh->cmd->dup)
        open_redirect(sh);
    sh->pipe = (1 < sh->size);
    if (sh->cmd == NULL)
        return ;
    exe_initialize(sh, &flg);
    hold(sh, &flg);  // to do
}