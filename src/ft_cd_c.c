/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:14:49 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/24 19:41:03 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_cd_back(char *cwd, t_env *envp)
{
	char	*var;

	var = ft_search_env("OLDPWD", envp);
	chdir(var);
	ft_env_owd(cwd, envp);
	ft_env_cwd(envp);
	return (1);
}

int		ft_cd_dir(char *cwd, t_env *envp, char **args)
{
	chdir(args[1]);
	ft_env_owd(cwd, envp);
	ft_env_cwd(envp);
	return (1);
}

void	ft_cd_int(char *var, char **args, char *cwd)
{
	var = ft_changedir(args[1], cwd);
	if (access(var, F_OK) == 0)
	{
		if (access(var, X_OK) == 0)
			chdir(var);
		else
		{
			ft_putstr("cd: permission denied: ");
			ft_putendl(args[1]);
		}
	}
	else
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(args[1]);
	}
	ft_strdel(&var);
}

int		ft_cd_glob(char *home, char **args, t_env *envp, char *var)
{
	char	*cwd;
	char	buff[PATH_MAX + 1];
	int		i;

	cwd = getcwd(buff, PATH_MAX + 1);
	i = ft_argslen(args);
	if (i == 1)
		chdir(home);
	else if (i == 2)
	{
		if (ft_strcmp(args[1], "-") == 0)
			return (ft_cd_back(cwd, envp));
		else
		{
			if (args[1][0] == '/')
				return (ft_cd_dir(cwd, envp, args));
			else
			{
				if (cwd)
					ft_cd_int(var, args, cwd);
			}
		}
	}
	return (1);
}
