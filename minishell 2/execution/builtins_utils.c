/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:22:45 by hel-haji          #+#    #+#             */
/*   Updated: 2024/11/21 13:22:45 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **fill_env_array(t_env *env, char **arr)
{
    t_env   *cur;
    int     i;

    i = 0;
    cur = env;
    while (cur)
    {
        arr[i] = env_head(cur);
        if (!arr[i])
        {
            while (i > 0)
                free(arr[--i]);
            free(arr);
            return (NULL);
        }
        i++;
        cur = cur->next;
    }
    arr[i] = NULL;
    return (arr);
}

char    **convert_lst(t_env *env)
{
    int     i;
    char    **arr;

    i = nodes_count(env);
    arr = malloc((i + 1) * sizeof(char *));
    if (!arr)
        return (NULL);
    return (fill_env_array(env, arr));
}

int nodes_count(t_env *env)
{
    int i;
    t_env *tmp;

    i = 0;
    tmp = env;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }

    return (i);
}

char    *env_entry(t_env *node)
{
	char	*entry;
	char	*tmp;

	entry = NULL;
	tmp = ft_strjoin(node->name, "=");
	if (tmp)
	{
		if (node->value)
			entry = ft_strjoin(tmp, node->value);
		else
			entry = ft_strdup(tmp);
		free(tmp);
	}
	return (entry);
}

char    *path_search(char **env, char *comnd)
{
    char **str;
    char *p_exe;
    char *p_env;

    if (*comnd == '\0' || env == NULL)
        return (NULL);
    if (ft_strchr(comnd, '/'))
        return (comnd_handler(comnd));
    p_env = extract_path(env);
    if (!p_env)
        return (NULL);
    str = ft_split(p_env, ':');
    if (!str)
        return (NULL);
    p_exe = find_exe_path(str, comnd);
    clear_tab(str);  // to do
    return p_exe;
}
