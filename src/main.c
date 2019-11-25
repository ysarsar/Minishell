/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:00:39 by ysarsar           #+#    #+#             */
/*   Updated: 2019/11/25 03:17:37 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_list(t_env *list)
{
    while (list)
    {
        ft_strdel(&list->data);
        list = list->next;
    }
    free(list);
}

int     main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_env   *envp;

    envp = my_getenv(env);
    msh_loop(envp);
    free_list(envp);
    return (0);
}




t_env   *my_getenv(char **env)
{
    int i;
    t_env   *head;
    t_env   *envp;
    
    envp = NULL;
    if (!(head = (t_env *)ft_memalloc(sizeof(t_env))))
        return (envp);
    head->next = NULL;
    envp = head;
    i = 0;
    while (env[i] != NULL)
    {
        envp->data = ft_strdup(env[i]);
        if (env[i + 1] != NULL)
        {
            if (!(envp->next = (t_env *)ft_memalloc(sizeof(t_env))))
                return (NULL);
        }
        envp = envp->next;
        i++;
    }
    return (head);
}