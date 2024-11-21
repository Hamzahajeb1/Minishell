#include "minishell.h"

void    home(t_data *sh)
{
    char    *p;
    char    *paths[2];

    paths[0] = NULL;
    paths[1] = NULL;
    if (!is_home(sh->env)) // to work
    {
        ft_putstr_fd("cd : HOME not set\n", STDERR_FILENO);
        sh->ext_status = EXIT_FAILURE;
        return ;
    }
    check_pwd(sh, &paths[1], &paths[0]);  // to work
    if (sh->ext_status = EXIT_FAILURE)
        return ;
    p = extract_env(sh->env, "HOME");
    to_home(sh, p); // to work
    if (paths[1])
        free(paths[1]);
}

void    ft_cd(t_data *sh)
{
    char    *curr_dir;
    
    curr_dir = getcwd(NULL, PATH_MAX);
    if (curr_dir == NULL)
        curr_dir = ft_strdup(extract_env(sh->env, "PWD"));
    if (2 < sh->argc)
    {
        ft_putstr_fd("cd : too many arguments\n", STDERR_FILENO);
        sh->ext_status = EXIT_FAILURE;
        if (curr_dir != NULL)
            free(curr_dir);
        return ;
        if (!ft_strnstr(sh->cmd->argv[1], "~", ft_strlen(sh->cmd->argv[1]))
        || sh->cmd->argv[1] == NULL)
            home(sh);
        else if (!ft_strncmp(sh->cmd->argv[1], "-", ft_strlen(sh->cmd->argv[1])))
            last_pwd_swap(sh); //to work
        else
            change_dir(sh, sh->cmd->argv[1]); //to wrok
        free(curr_dir);
    }
}