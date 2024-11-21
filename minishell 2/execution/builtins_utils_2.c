/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:22:39 by hel-haji          #+#    #+#             */
/*   Updated: 2024/11/21 13:22:39 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *create_exe_path(char *path, char *comnd)
{
    char    *p_exe;
    char    *tmp;

    tmp = ft_strjoin(path, "/");
    p_exe = ft_strjoin(tmp, comnd);
    free(tmp);
    if (0 == access(p_exe, F_OK | X_OK))
        return (p_exe);
    free(p_exe);
    return (NULL);
}

char    *find_exe_path(char **path, char *comnd)
{
    int     count;
    char    *p_exe;
    
    count = 0;
    while (path[count])
    {
        p_exe = create_exe_path(path[count], comnd);
        if (p_exe != NULL)
            return (p_exe);
        count++;
    }
    return (NULL);
}


char    *extract_path(char **env)
{
    while (*env)
    {
        if (ft_strncmp(*env, "PATH=", 5) == 0)
            return (*env + 5);
        env++;
    }
    return (NULL);
}

char	*comnd_handler(char *comnd)
{
	if (-1 == access(comnd, X_OK))
	{
		ft_putstr_fd(comnd, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		exit(126);
	}
	else if (-1 == access(comnd, F_OK))
	{
		ft_putstr_fd(comnd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(127);
	}
	return (comnd);
}