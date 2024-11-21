#include "minishell.h"

t_env	*find(t_env *env, char *name)
{
	while (env)
	{
		if (ft_(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	free_env(void *data)
{
	static t_track	*save;
	t_track			*to_free;
	t_track			**curr;
	
	save = NULL;
	curr = &save;
	while(*curr)
	{
		if((*curr)->adrs == data)
		{
			to_free = *curr;
			*curr = (*curr)->next;
			free(to_free);
			free(data);
			return;
		}
		curr = &((*curr)->next);
	}
}

void	rm_track(void *data)
{
	static	t_track	*save;
	t_track			**curr;
	t_track			*to_free;
	
	save = NULL;
	curr = &save;
	while (*curr)
	{
		if ((*curr)->adrs == data)
		{
			to_free = *curr;
			*curr = (*curr)->next;
			free(to_free);
			return;
		}
		curr = &((*curr)->next);
	}
}

void	ft_remove(t_env **env, t_env *target)
{
	t_env	**curr;
	t_env	*to_free;
	
	curr = env;
	while(*curr)
	{
		if (*curr == target)
		{
			to_free = *curr;
			*curr = (*curr)->next;
			free_env(to_free->name);
			free_env(to_free->value);
			rm_track(to_free);
			return;
		}
		curr = &((*curr)->next);
	}
}