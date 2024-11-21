#include "minishell.h"

char	extract_env(t_env *env, char *name)
{
	size_t	i;
	
	i = ft_strlen(name);
	while(env)
	{
		if ((env->name[i] == '\0' || env->name[i] == '=') && !ft_strncmp(env->name, name, i))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_pwd(t_data *sh)
{
	int		out_fd;
	char	*env_fd;
	char	*res;
	char	cur_dir[PATH_MAX];

	out_fd = sh->cmd->out_fd;
	res = getcwd(cur_dir, PATH_MAX);
	if(res)
	{
		ft_putendl_fd(cur_dir, out_fd);
		sh->ext_status = EXIT_SUCCESS;
	}
	else
	{
		env_fd = extract_env(sh->env, "PWD");
		if (env_fd)
		{
			ft_putendl_fd(env_fd, out_fd);
			sh->ext_status = EXIT_SUCCESS;
		}
		else
		{
			ft_putendl_fd(PWD_ERR, out_fd);
			sh->ext_status = EXIT_FAILURE;
		}
	}
}