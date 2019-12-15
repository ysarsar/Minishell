/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:47:55 by root              #+#    #+#             */
/*   Updated: 2019/12/12 20:41:04 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_env **envp, char *path, int c)
{
	t_env *current;

	current = *envp;
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

int		ft_setenv(t_env **envp, char **args, char *path)
{
	int		i;
	char	*var;

	i = ft_argslen(args);
	if (i == 1)
		ft_env(envp, path, 1);
	else if (i == 2)
	{
		if (!ft_isalpha(args[1][0]))
			return (print_error(1));
		ft_modify_env(envp, args, 2);
	}
	else if (i == 3)
	{
		if (!ft_isalpha(args[1][0]))
			return (print_error(1));
		ft_modify_env(envp, args, 3);
	}
	else
		return (print_error(2));
	return (1);
}

void	ft_unsetenv(t_env **envp, char **args)
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

int		ft_cd(char **args, char *home, t_env *envp)
{
	int		i;
	char	*var;
	char	*cwd;
	char	buff[PATH_MAX + 1];

	i = ft_argslen(args);
	cwd = getcwd(buff, PATH_MAX + 1);
	if (i > 2)
		ft_putendl("cd: Too many arguments.");
	else
	{
		ft_cd_glob(home, args, envp, var);
		ft_env_owd(cwd, envp);
		ft_env_cwd(envp);
		return (1);
	}
	return (1);
}

int		ft_echo(char **args)
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
