/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:09:05 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/24 20:20:12 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_reg;

void	free_args(char **args)
{
	int i;

	if (args)
	{
		i = 0;
		while (args[i])
		{
			ft_strdel(&args[i]);
			i++;
		}
		free(args);
	}
}

void	my_func(int seg)
{
	ft_putchar('\n');
	if (g_reg != 1)
		ft_prompt();
	g_reg = -1;
}

void	msh_loop(t_env **envp)
{
	char	*line;
	char	**args;
	char	**tab;
	int		status;

	status = 1;
	while (status)
	{
		g_reg = 0;
		if (g_reg == 0)
			ft_prompt();
		if ((line = msh_read_line()) != NULL && line[0] != '\0')
		{
			if ((args = split_shell(line, envp)) != NULL && args[0] != NULL)
			{
				tab = list_to_tab(envp);
				g_reg = 1;
				status = msh_execute(args, envp, tab);
				free_args(tab);
			}
			free_args(args);
			ft_strdel(&line);
		}
		free(line);
	}
}

char	*msh_read_line(void)
{
	char	*line;
	int		status;

	status = 0;
	line = NULL;
	status = get_next_line(1, &line);
	if (status == 1)
		return (line);
	return (NULL);
}
