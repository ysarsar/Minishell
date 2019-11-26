/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:41:39 by ysarsar           #+#    #+#             */
/*   Updated: 2019/11/26 05:49:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		msh_execute(char **args, t_env *envp, char **tab)
{
	char	*path;
	int		i;

	path = valide_path(args, envp);
	if ((i = check_builtins(args, envp, path)))
	{
		if (i == 2)
			return (0);
		return (1);
	}
	else if (args[0][0] == '/' || args[0][0] == '.')
	{
		execute_without_env(args, tab);
		return (1);
	}
	else
	{
		execute_with_env(args, envp, tab);
		return (1);
	}
	return (1);
}

int		check_builtins(char **args, t_env *envp, char *path)
{
	char	*home;

	home = ft_search_env("HOME", envp);
	if (ft_strcmp(args[0], "env") == 0)
	{
		ft_env(envp, path, 0);
		return (1);
	}
	else if (ft_strcmp(args[0], "setenv") == 0)
	{
		ft_setenv(envp, args, path);
		return (1);
	}
	else if (ft_strcmp(args[0], "unsetenv") == 0)
	{
		ft_unsetenv(envp, args);
		return (1);
	}
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		ft_cd(args, home, envp);
		return (1);
	}
	else if (ft_strcmp(args[0], "exit") == 0)
		return(2);
	else if (ft_strcmp(args[0], "echo") == 0)
	{
		ft_echo(args);
		return (1);
	}
	return (0);
}

char	*ft_search_env(char *str, t_env *envp)
{
	t_env *current;

	current = envp;
	while (current)
	{
		if (ft_strncmp(current->data, str, ft_strlen(str)) == 0)
			return (&(current->data[ft_datalen(current->data) + 2]));
		current = current->next;
	}
	return (NULL);
}

char	*ft_changedir(char *str, char *cwd)
{
	char	*var;
	char	*path;

	var = ft_strjoin(cwd, "/");
	path = ft_strjoin(var, str);
	ft_strdel(&var);
	return (path);
}
