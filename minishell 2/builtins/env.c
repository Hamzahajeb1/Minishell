/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:09:53 by hel-haji          #+#    #+#             */
/*   Updated: 2024/10/21 16:09:53 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    put_err(t_data *sh, int fd)
{
    ft_putstr_fd("env ‘", fd);
    ft_putstr_fd(sh->comnd->argv[1], fd);
    ft_putstr_fd("’: No such file or directory\n", fd);
    sh->ext_status = EXIT_FAILURE;
}

void    putdata(t_env *data, int fd)
{
    ft_putstr_fd(data->name, fd);
    ft_putstr_fd("=", fd);
    ft_putstr_fd(data->value, fd);
    ft_putstr_fd("\n", fd);
}

void    ft_env(t_data *sh)
{
    t_env   *dir;
    int     fd;
    
    dir = sh->env;
    fd = sh->comnd->out_fd;
    if (sh->argc == 1)
    {
        while(dir)
        {
            if (dir->value)
                putdata(dir, fd);
            dir = dir->next;
        }
    }
    else
        put_err(sh, fd);
}