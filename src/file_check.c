/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 19:16:25 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:26:36 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		file_check(char **args, t_env **envp, int set)
{
	char	*p;
	char	*str2;
	char	*str1;
	char	**path;
	int		i;

	i = 0;
	p = find_path(envp);
	path = ft_strsplit(&p[5], ':');
	if (p != NULL)
	{
		while (path[i])
		{
			if (check_file(args, set, path[i]))
			{
				free_args(path);
				return (1);
			}
			i++;
		}
	}
	free_args(path);
	return (0);
}

int		check_file(char **args, int set, char *path)
{
	char	*str1;
	char	*str2;

	str1 = ft_strjoin(path, "/");
	str2 = ft_strjoin(str1, args[0]);
	ft_strdel(&str1);
	if (set)
	{
		if (access(str2, F_OK) == 0)
		{
			ft_strdel(&str2);
			return (1);
		}
	}
	else
	{
		if (access(str2, X_OK) == 0)
		{
			ft_strdel(&str2);
			return (1);
		}
	}
	ft_strdel(&str2);
	return (0);
}

char	*find_path(t_env **envp)
{
	t_env	*current;

	current = *envp;
	while (current != NULL)
	{
		if (ft_strncmp(current->data, "PATH=", 5) == 0)
			return (current->data);
		current = current->next;
	}
	return (NULL);
}

char	*valide_path(char **args, t_env **envp)
{
	char	*p;
	char	*str1;
	char	*str2;
	char	**path;
	int		i;

	i = 0;
	if (!(p = find_path(envp)))
		return (NULL);
	path = ft_strsplit(&p[5], ':');
	while (path[i])
	{
		str1 = ft_strjoin(path[i], "/");
		str2 = ft_strjoin(str1, args[0]);
		ft_strdel(&str1);
		if (access(str2, F_OK) == 0)
		{
			free_args(path);
			return (str2);
		}
		i++;
		ft_strdel(&str2);
	}
	free_args(path);
	return (NULL);
}
