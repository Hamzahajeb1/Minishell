/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:25:18 by hel-haji          #+#    #+#             */
/*   Updated: 2024/11/21 13:25:18 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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