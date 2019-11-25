/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:44:58 by ysarsar           #+#    #+#             */
/*   Updated: 2019/11/25 03:17:46 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		replace(char **str, int i, char c)
{
	char *arr;

	i++;
	arr = *str;
	while (arr[i])
	{
		if (arr[i] == c)
			break ;
		else if (arr[i] == ' ')
			arr[i] = -1;
		else if (arr[i] == '\t')
			arr[i] = -2;
		i++;
	}
	if (arr[i] == '\0')
	{
		ft_putstr("Unmatched ");
		ft_putchar(c);
		ft_putendl(".");
		return (-1);
	}
	return (i);
}

char	*msh_split(char *str)
{
	int		i;
	char	*s;

	s = ft_strdup(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i = replace(&s, i, str[i]);
		if (i == -1)
		{
			ft_strdel(&s);
			return (NULL);
		}
		i++;
	}
	return (s);
}

char	*trim_arr(char *str)
{
	char *arr;

	arr = str;
	if (arr[0] == '\"' || arr[0] == '\'')
		arr = ft_strtrim(arr, arr[0]);
	return (arr);
}

char	*space(char *str)
{
	char	*s;
	int		i;

	i = 0;
	s = str;
	while (s[i])
	{
		if (s[i] == -1)
			s[i] = ' ';
		else if (s[i] == -2)
			s[i] = '\t';
		i++;
	}
	return (s);
}

char	**split_shell(char *str)
{
	char	*tmp;
	char	**arr;
	int		i;

	i = -1;
	if (!(tmp = msh_split(str)))
		return (NULL);
	arr = ft_strtok(tmp, "\t\n ");
	while (arr[++i])
		arr[i] = trim_arr(arr[i]);
	i = -1;
	while (arr[++i])
		arr[i] = space(arr[i]);
	free(tmp);
	return (arr);
}
