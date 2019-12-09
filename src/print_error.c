/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 12:49:22 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/09 13:04:23 by ysarsar          ###   ########.fr       */
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
