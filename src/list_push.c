/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 03:00:32 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:26:41 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	listpush(char *var, t_env **envp)
{
	t_env	*new_node;
	t_env	*last;

	if (!(new_node = (t_env*)ft_memalloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	last = *envp;
	new_node->data = ft_strdup(var);
	new_node->next = NULL;
	if (*envp == NULL)
	{
		*envp = new_node;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new_node;
	return ;
}
