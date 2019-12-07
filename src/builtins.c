/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:47:55 by root              #+#    #+#             */
/*   Updated: 2019/12/07 12:47:12 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_env *envp, char *path, int c)
{
	t_env *current;

	current = envp;
	if (access(path, F_OK) == 0 || c == 1)
	{
		while (current != NULL)
		{
			ft_putendl(current->data);
			current = current->next;
		}
	}
	else
		ft_putendl("env: command not found.");
	return (1);
}

void	ft_setenv(t_env *envp, char **args, char *path)
{
	int		i;
	char	*var;

	i = ft_argslen(args);
	if (i == 1)
		ft_env(envp, path, 1);
	else if (i == 2)
	{
		if (!ft_isalpha(args[1][0]))
		{
			ft_putendl("setenv: Variable name must begin with a letter.");
			return ;
		}
		ft_modify_env(envp, args, 2);
	}
	else if (i == 3)
	{
		if (!ft_isalpha(args[1][0]))
		{
			ft_putendl("setenv: Variable name must begin with a letter.");
			return ;
		}
		ft_modify_env(envp, args, 3);
	}
	else
	{
		ft_putendl("setenv: too many arguments.");
		return ;
	}
}

void	ft_unsetenv(t_env *envp, char **args)
{
	int		i;

	i = ft_argslen(args);
	if (i >= 2)
	{
		i = 1;
		while (args[i])
		{
			delete_var(envp, args[i]);
			i++;
		}
	}
	else
		ft_putendl("unsetenv: Too few arguments.");
	
}

void	ft_cd(char **args, char *home, t_env *envp)
{
	int		i;
	char	*var;
	char	*cwd;
	char	*str;
	char	buff[PATH_MAX +1];

	i = ft_argslen(args);
	cwd = getcwd(buff, PATH_MAX +1);
	if (i > 2)
		ft_putendl("cd: Too many arguments.");
	else
	{
		if (i == 1)
			chdir(home);
		else if (i == 2)
		{
			if (ft_strcmp(args[1], "-") == 0)
			{
				var = ft_search_env("OLDPWD", envp);
				chdir(var);
				ft_env_owd(cwd, envp);
				str = ft_env_cwd(envp);
				return ;
			}
			else
			{
				if (args[1][0] == '/')
				{
						chdir(args[1]);
						ft_env_owd(cwd, envp);
						str = ft_env_cwd(envp);
						return ;
				}
				else
				{
					if (cwd)
					{
						var = ft_changedir(args[1], cwd);
						chdir(var);
						ft_strdel(&var);
					}
				}
			}
		}
		ft_env_owd(cwd, envp);
		str = ft_env_cwd(envp);
	}
}

int	ft_echo(char **args)
{
	int		i;

	i = 1;
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1] != NULL)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (1);
}
