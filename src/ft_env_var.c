/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 02:03:50 by ysarsar           #+#    #+#             */
/*   Updated: 2019/11/25 03:17:29 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env_owd(char *cwd, t_env *envp)
{
    t_env   *current;
    char    *var;

    current = envp;
    while (current)
    {
        if (strncmp("OLDPWD=", current->data, ft_strlen("OLDPWD=")) == 0)
            break ;
        current = current->next;
    }
    var = ft_strjoin("OLDPWD=", cwd);
    current->data = var;
}
void    ft_env_cwd(t_env *envp)
{
    t_env   *current;
    char    *var;
    char    buff[PATH_MAX +1];
    char    *cwd;

    current = envp;
    while (current)
    {
        if (ft_strncmp("PWD=", current->data, ft_strlen("PWD=")) == 0)
            break;
        current = current->next;
    }
    cwd = getcwd(buff, PATH_MAX + 1);
    current->data = ft_strjoin("PWD=", cwd);
}