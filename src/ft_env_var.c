/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 02:03:50 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/09 12:27:19 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_owd(char *cwd, t_env *envp)
{
	t_env	*current;
	char	*var;

	current = envp;
	while (current)
	{
		if (strncmp("OLDPWD=", current->data, ft_strlen("OLDPWD=")) == 0)
			break ;
		current = current->next;
	}
	var = ft_strjoin("OLDPWD=", cwd);
	if (current)
	{
		free(current->data);
		current->data = var;
	}
	else
		listpush("OLDPWD=", &envp);
}

void	ft_env_cwd(t_env *envp)
{
	t_env	*current;
	char	buff[PATH_MAX + 1];
	char	*cwd;

	current = envp;
	while (current)
	{
		if (ft_strncmp("PWD=", current->data, ft_strlen("PWD=")) == 0)
			break ;
		current = current->next;
	}
	cwd = getcwd(buff, PATH_MAX + 1);
	if (current)
	{
		free(current->data);
		current->data = ft_strjoin("PWD=", cwd);
	}
	else
		listpush("PWD=", &envp);
}

void	ft_prompt(void)
{
	char	*cwd;
	char	buff[PATH_MAX];

	cwd = getcwd(buff, PATH_MAX + 1);
	if (cwd == NULL)
		exit(0);
	ft_putstr("\033[1;36m");
	ft_putchar('[');
	ft_putstr(cwd);
	ft_putchar(']');
	ft_putstr("\033[0m");
	ft_putstr("\033[1;34m");
	ft_putstr(" $> ");
	ft_putstr("\033[0m");
}
