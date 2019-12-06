/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modify_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 21:46:18 by root              #+#    #+#             */
/*   Updated: 2019/12/06 17:22:56 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_argslen(char **args)
{
    int     i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

int     ft_datalen(char *data)
{
    int     i;

    i = 0;
    while (data[i] != '\0')
    {
        if (data[i] == '=')
            break;
        i++;
    }
    return (i - 1);
}

void    ft_modify_env(t_env *envp, char **args, int count)
{
    char    *var;
    t_env   *current;
    int     c;

    current = envp;
    c = 0;
    if (count == 3)
    {
        var = ft_strcat(args[1], "=");
        var = ft_strcat(var, args[2]);
    }
    else if (count == 2)
        var = ft_strcat(args[1], "=");
    while (current)
    {
        if (ft_strncmp(current->data, args[1], ft_datalen(current->data)) == 0)
        {
            ft_strdel(&current->data);
            current->data = ft_strdup(var);
            c++;
            break;
        }
        current = current->next;
    }
    if (c == 0)
        listpush(var, &envp);
}

void    delete_var(t_env *envp, char *arg)
{
    t_env   *temp;
    t_env   *prev;

    temp = envp;
    if (temp != NULL && (ft_strncmp(temp->data, arg, ft_datalen(temp->data) == 0)))
    {
        envp = temp->next;
        ft_strdel(&temp->data);
        free(temp);
        return ;
    }
    while (temp != NULL && (ft_strncmp(temp->data, arg, ft_datalen(temp->data)) != 0))
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return ;
    prev->next = temp->next;
    ft_strdel(&temp->data);
    free(temp);
}