/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 12:49:22 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 17:54:56 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_error(int c)
{
	if (c == 1)
		ft_putendl("setenv: Variable name must begin with a letter.");
	else if (c == 2)
		ft_putendl("setenv: too many arguments.");
	return (1);
}

void	exec_error(char *str, int c)
{
	if (c == 1)
	{
		ft_putstr(str);
		ft_putendl(": Permission denied.");
	}
	else if (c == 2)
	{
		ft_putstr(str);
		ft_putendl(": Command not found.");
	}
}

void	change_home(t_env **envp, char **arg)
{
	char	*key;
	char	*tmp;

	key = ft_search_env("HOME", *envp);
	tmp = ft_strdup(*arg + 1);
	free(*arg);
	*arg = ft_strjoin(key, tmp);
	ft_strdel(&tmp);
}

char	**line_error(char *str)
{
	ft_putstr(str);
	ft_putendl(": Undefined variable.");
	ft_strdel(&str);
	return (NULL);
}
