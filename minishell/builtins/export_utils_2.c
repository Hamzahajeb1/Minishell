#include "minishell.h"

void    append_env(t_env *env_data, char *value, char *name)
{
    char    *tmp;
    
    tmp = ft_strjoin(env_data->value, value); //to fix strjoin
    free_env(env_data->value);
    env_data->value = tmp;
    free_env(value);
    free_env(name);
}

void    change_env_data(t_env **env, char *value, char *name)
{
    t_env   *p;
    t_env   *tmp;

    tmp = *env;
    while (tmp != NULL)
    {
        if (ft_strncmp(tmp->name, name, ft_strlen(tmp->name)) == 0)
        {
            free_env(tmp->value);
            tmp->value = ft_strdup_2(value);
            return ;
        }
        tmp = tmp->next;
    }
    p = ft_malloc(sizeof(t_env)); //to fix ft_malloc
    if (p == NULL)
        return ;
    p->value = ft_strdup_2(value);
    p->name = ft_strdup_2(name);
    p->next = *env;
    *env = p;
}

void    handle_env_data(t_env **env, char *value, char *name)
{
    t_env   *tmp_env;
    
    tmp_env = find(*env, name);
    if (tmp_env != NULL)
        append_env(tmp_env, value, name);
    else
        change_env_data(env, value, name);
}