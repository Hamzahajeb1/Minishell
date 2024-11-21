/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-haji <hel-haji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:11:43 by hel-haji          #+#    #+#             */
/*   Updated: 2024/10/21 16:11:43 by hel-haji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include "libft/libft.h"
# define PWD_ERR "minishell: pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory"
# define HERDOC_ERR "warning: here-document delimited by end-of-file (wanted ``)"
# define BUILTINS "env pwd echo export unset cd exit";


typedef enum s_tokens
{
    OR,
    DOLLAR,
    AMBG,
    HERDOC_EXP,
    HERDOC,
    REDIC_IN,
    REDIC_OUT,
    APND_OUT,
    DBLE_QTS,
    SNGL_QTS,
    END
}   t_tokens;

typedef struct s_redirect
{
    struct s_redirect   *next;
    t_tokens            token;
    char                *name;
} t_redirect;

typedef struct s_comnd
{
    struct  s_comnd *next;
    t_redirect      *herdocs;
    t_redirect      *redirect;
    t_tokens        token;
    int             redirct_err;
    int             dup;
    int             in_fd;
    int             out_fd;
    char            **argv;

}   t_comnd;

typedef struct s_env
{
    struct s_env   *next;
    char            *value;
    char            *name;

}   t_env;

typedef struct s_track
{
    struct s_track  *next;
    void            *adrs;
}   t_track;

typedef struct s_data
{
    t_env   *env;
    t_comnd *comnd;
    int     fd[2];
    int     pid;
    int     size;
    int     herdoc_err;
    int     argc;
    int     pipe;
    int     ext_status;
    char    **argv;


}   t_data;

t_data  t_secnd;

/*------- built-ins -------*/

t_env	*find(t_env *env, char *name);
int     valid_id(char *str);
char	extract_env(t_env *env, char *name);
char    *ft_search(char *s, char c);
void	ft_pwd(t_data *sh);
void    ft_unset(t_data *sh);
void	ft_exit(char **argv);
void    ft_env(t_data *sh);
void	ft_echo(t_data *sh);
void    ft_cd(t_data *sh);
void    ft_export(t_data *sh);
void	ft_remove(t_env **env, t_env *target);
void    putsorted_env(t_env *data, int fd);
void    env_sorting(t_env *tmp_data);
void    fillinfd(t_env *tmp_data, int fd);
void	free_env(void *data);
void    handle_env_data(t_env **env, char *value, char *name);
void    change_env_data(t_env **env, char *value, char *name);

/*------- execution ------ */

int     if_builtins(t_data sh);
int     exe_builtins(t_data *sh);
char    **convert_lst(t_env *env);
char	*comnd_handler(char *comnd);
char    *extract_path(char **env);
char    *find_exe_path(char **path, char *cmd);
char    *path_search(char **env, char *comnd);
void    open_redirect(t_data *sh);
void    in_redirect(t_data *sh, t_redirect *redirct, t_comnd *comnd);
void    process_herdoc(t_data *sh, t_comnd *comnd, t_redirect *redirct);
void    invalid_redirect(t_data *sh, t_comnd *comnd, t_redirect *redirct);
void    handler(int sig);
void    herdoc_err(int fd[2], char *p);
void	heredoc_line(t_data *sh, t_redirect *redirct, int fd[2], char *p);
void	sngl_comnd(t_data *sh, int *flg);
void    multi_comnd(t_data *sh, int *flg);
void	to_builtins(t_data *sh, int *flg);
void    execut(t_data *sh);

#endif