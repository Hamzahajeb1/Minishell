#include "minishell.h"

void    fillinfd(t_env *tmp_data, int fd)
{
    ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(tmp_data->name, fd);
	if (tmp_data->value)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(tmp_data->value, fd);
		ft_putstr_fd("\"", fd);
	}
	ft_putstr_fd("\n", fd);
}

void    putsorted_env(t_env *data, int fd)
{
    t_env   *tmp;
    
    tmp = data;
    env_sorting(tmp);
    while (tmp)
    {
        if (ft_strncmp(tmp->name, "_", ft_strlen(tmp->name)) != 0)
            fillinfd(tmp, fd);
        tmp = tmp->next;
    }
}

void    exporting(t_env **env, char *data)
{
    char    *p;
    
    p = ft_search(data, '=');
    if (p)
        env_handling(env, data, p);
    else 
        new_env_handling();
}

void    putinerr(t_data *data, int fd, char *i)
{
    ft_putstr_fd("minishell: export: `", fd);
	ft_putstr_fd(i, fd);
	ft_putstr_fd("`: not a valid identifier\n", fd);
	data->ext_status = EXIT_FAILURE;
}

void    ft_export(t_data *sh)
{
    int fd;
    int i;
    
    fd = sh->cmd->out_fd;
    i = 1;
    if (sh->argc == 1)
    {
        putsorted_env(sh->env, fd);
        return;
    }
    while (sh->cmd->argv[i])
    {
        if (!valid_id(sh->cmd->argv[i]))
            putinerr(sh, fd, sh->cmd->argv[i]);
        else
            exporting(&(sh->env), sh->cmd->argv[i]);
        i++;
    }
    sh->ext_status = EXIT_SUCCESS;
} 