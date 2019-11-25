/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 21:35:02 by ysarsar           #+#    #+#             */
/*   Updated: 2019/11/25 03:17:35 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **list_to_tab(t_env *envp)
{
    t_env   *current;
    char    **tab;
    int     i;

    current = envp;
    i = 0;
    while (current != NULL)
    {
        current = current->next;
        i++;
    }
    tab = (char **)ft_memalloc(sizeof(char*) * (i + 1));
    i = 0;
    current = envp;
    while (current != NULL)
    {
        tab[i] = ft_strdup(current->data);
        current = current->next;
        i++;
    }
    tab[i] = NULL;
    return (tab);
}