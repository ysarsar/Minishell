/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 21:26:07 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/09 13:06:01 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_without_env(char **args, char **tab)
{
	pid_t	pid;
	pid_t	wpid;

	pid = fork();
	if (pid == 0)
	{
		if (access(args[0], F_OK) == 0)
		{
			if (access(args[0], X_OK) == 0)
			{
				if (execve(args[0], args, tab) == -1)
					ft_putendl("Minishel : Error exec.");
			}
			else
				exec_error(args[0], 1);
		}
		else
			exec_error(args[0], 2);
		exit(1);
	}
	else if (pid < 0)
		ft_putendl("Minishell : Error forking.");
	else
		wpid = wait(NULL);
}

void	error_msg(char *str)
{
	ft_putstr(str);
	ft_putendl(": command not found.");
}

void	execute_with_env(char **args, t_env **envp, char **tab)
{
	char	*path;

	path = valide_path(args, envp);
	if (!path)
	{
		error_msg(args[0]);
		return ;
	}
	if (file_check(args, envp, 1))
	{
		if (file_check(args, envp, 0))
			msh_lunche(path, args, tab);
		else
		{
			ft_putstr(args[0]);
			ft_putendl((": Permission denied."));
		}
	}
	ft_strdel(&path);
}

void	msh_lunche(char *path, char **args, char **tab)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, tab) == -1)
			ft_putendl("Minishell: error exec");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		ft_putendl("Minishell: error forking");
	else
		wpid = wait(NULL);
}
