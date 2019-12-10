/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:31:42 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/10 23:01:04 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_expantions(char **args, t_env **envp)
{
	int		i;
	char	*var;
	char	*key;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '~' && !(ft_isalpha(args[i][1])))
		{
			key = ft_search_env("HOME", *envp);
			tmp = ft_strdup(args[i] + 1);
			free(args[i]);
			args[i] = ft_strjoin(key, tmp);
			ft_strdel(&tmp);
		}
		if (ft_is_there(args[i], '$'))
		{
			if ((var = ft_var_name(args[i])) == NULL)
				break ;
			key = ft_search_env(var, *envp);
			if (key == NULL)
			{
				ft_putstr(var);
				ft_putendl(": Undefined variable.");
				ft_strdel(&var);
				return (NULL);
			}
			tmp = ft_change_arg(key, args[i], var);
			ft_strdel(&args[i]);
			args[i] = ft_strdup(tmp);
			ft_strdel(&tmp);
			ft_strdel(&var);
		}
		i++;
	}
	return (args);
}

char	*ft_var_name(char *str)
{
	int		i;
	int		j;
	char	tmp[1024];
	char	*var;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	if (str[i] == '\0' || str[i] == '$')
		return (NULL);
	while (str[i])
	{
		if (is_special(str[i]))
			break ;
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	var = ft_strdup(tmp);
	return (var);
}

int		is_special(char c)
{
	if (c == '#' || c == '/' || c == '~' || c == '@'
		|| c == '^' || c == '$')
		return (1);
	return (0);
}

char	*ft_change_arg(char *key, char *str, char *var)
{
	int		i;
	int		j;
	int		k;
	char	tmp[1024];

	i = -1;
	j = -1;
	while (str[++i] != '$')
		tmp[i] = str[i];
	k = i;
	while (key[++j])
	{
		tmp[i] = key[j];
		i++;
	}
	j = k + ft_strlen(var) + 1;
	while (str[j])
	{
		tmp[i] = str[j];
		j++;
		i++;
	}
	tmp[i] = '\0';
	return (ft_strdup(tmp));
}
