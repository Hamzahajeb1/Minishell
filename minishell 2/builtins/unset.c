/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:10:47 by hel-haji          #+#    #+#             */
/*   Updated: 2024/10/21 16:10:47 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	getenv(char *data, t_env **env)
{
	t_env	*target;
	
	if (!*env)
		return;
	target = find(*env, data);
	if (target)
		ft_remove(env, target);
}

void    ft_unset(t_data *sh)
{
	int i;
	
	i = 1;
	while(sh->comnd->argv[i])
	{
		getenv(sh->comnd->argv[i], &(sh->env));
		i++;
	}
	sh->ext_status = EXIT_SUCCESS;
}