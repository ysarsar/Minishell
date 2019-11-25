/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:01:12 by ysarsar           #+#    #+#             */
/*   Updated: 2019/11/25 19:50:36 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFF_SIZE 3

# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
#include <limits.h>

typedef struct      s_env
{
    char            *data;
    struct  s_env   *next;
}                   t_env;

int     get_next_line(const int fd, char **line);
t_env   *my_getenv(char **env);

void    msh_loop(t_env *envp);
char    *msh_read_line();
char    **msh_split_line(char *line);
char    **split_shell(char *str);
char    **list_to_tab(t_env *envp);
char    *find_path(t_env *envp);
char    *valide_path(char **args, t_env *envp);
void	execute_without_env(char **args, char **tab);
void	execute_with_env(char **args, t_env *envp, char **tab);
int		msh_execute(char **args, t_env *envp, char **tab);
int		check_builtins(char **args, t_env *envp, char *path);
void    ft_env(t_env *envp, char *path, int c);
int     ft_argslen(char **args);
void    ft_modify_env(t_env *envp, char **args, int count);
void    ft_setenv(t_env *envp, char **args, char *path);
int     ft_datalen(char *data);
void    listpush(char *var, t_env **envp);
void    delete_var(t_env *envp, char *arg);
void	ft_unsetenv(t_env *envp, char **args);
void	free_args(char **args);
int     file_check(char **args, t_env *envp, int set);
void    msh_lunche(char *path, char **args, char **tab);
char	*ft_search_env(char *str, t_env *envp);
void	ft_cd(char **args, char *home, t_env *envp);
void    ft_env_owd(char *cwd, t_env *envp);
void    ft_env_cwd(t_env *envp);
char	*ft_changedir(char *str, char *cwd);

#endif