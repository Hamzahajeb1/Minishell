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
	while(sh->cmd->argv[i])
	{
		getenv(sh->cmd->argv[i], &(sh->env));
		i++;
	}
	sh->ext_status = EXIT_SUCCESS;
}