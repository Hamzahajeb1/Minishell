/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:10:21 by hel-haji          #+#    #+#             */
/*   Updated: 2024/10/21 16:10:21 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int valid_id(char *str)
{
	int count;
	
	count = 1;
	if ((!ft_isalpha(str[0]) && str[0] != '_') || !str)
		retunr (0);
	while (str[count] && !(str[count] == '+' && str[count + 1] == '=') && str[count] != '=')
	{
		if (!ft_isalnum(str[count]) && str[count] != '_')
			return (0);
		count++;
	}
	return (1);
}

void    env_swaping(t_env *lst1, t_env *lsts2)
{
	char    *value;
	char    *name;
	
	value = lst1->value;
	name = lst1->name;
	lst1->value = lsts2->value;
	lst1->name = lsts2->name;
	lsts2->value = value;
	lsts2->name = name;
}

void    env_sorting(t_env *tmp_data)
{
	t_env   *curr;
	size_t  i;
	
	curr = tmp_data;
	i = ft_strlen(curr->name);
	if (!tmp_data)
		return;
	while (curr && curr->next)
	{
		if (ft_strncmp(curr->name, curr->next->name, i) > 0)
		{
			env_swaping(curr, curr->next);
			curr = tmp_data;
		}
		else
			curr = curr->next;
	}
}

char    *ft_search(char *s, char c)
{
	int i;
	
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

void    env_handling(t_env **env, char *data, char *p)
{
	char    *value;
	char    *name;
	
	if (*(p - 1) == '+')
	{
		value = ft_strdup_2(p + 1);
		name = ft_strdup_1(data, p - data - 1);
		handle_env_data(env, value, name);
	}
	else
	{
		value = ft_strdup_2(p + 1);
		name = ft_strdup_1(data, p - data + 1);
		change_env_data(env, value, name);
	}
}
