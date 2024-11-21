/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:22:50 by hel-haji          #+#    #+#             */
/*   Updated: 2024/11/21 13:22:50 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_builtins(t_data *sh)
{
	if (!ft_strcmp(sh->comnd->argv[0], "pwd"))
		ft_pwd(sh);
	else if (!ft_strcmp(sh->comnd->argv[0], "echo"))
		ft_echo(sh);
	else if (!ft_strcmp(sh->comnd->argv[0], "env"))
		ft_env(sh);
	else if (!ft_strcmp(sh->comnd->argv[0], "unset"))
		ft_unset(sh);
	else if (!ft_strcmp(sh->comnd->argv[0], "export"))
		ft_export(sh);
	else if (!ft_strcmp(sh->comnd->argv[0], "cd"))
		ft_cd(sh);
	else if (!ft_strcmp(sh->comnd->argv[0], "exit"))
		ft_exit(sh->comnd->argv);
	return (sh->ext_status);
}

void	to_builtins(t_data *sh, int *flg)
{
	if (0 == if_builtins(*sh))
		*flg = exe_builtins(sh);
	else
		*flg = 1;
	sh->ext_status = *flg;
}


void    execute_with_execve(t_data *sh, char *path)
{
    // struct stat path_stat;

    // if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) // to funcking do
    {
        handle_is_directory(path); // to do
        return ;
    }
    execve(path, sh->comnd->argv, sh->env);
    perror("minishell");
    exit(127);
}

char *find_executable_path(t_data *sh)
{
    char *path;

    sh->env = convert_lst(sh->env);
    path = path_search(sh->comnd->argv[0], sh->env);
    if (!path)
    {
        handle_exec_error(sh->comnd->argv[0]); //to do
        return (NULL);
    }
    return (path);
}

void    execut(t_data *sh)
{
    char *path;

    if (!sh->comnd || !sh->comnd->argv[0])
        return ;
    path = find_executable_path(sh);
    if (!path)
        return ;
    execute_with_execve(sh, path);
}
