/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 01:18:12 by oelazzou          #+#    #+#             */
/*   Updated: 2019/11/22 15:51:28 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_white(char c, char a)
{
	if (c == a)
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s, char a)
{
	int				end;
	unsigned int	start;
	char			*str;

	if (s == NULL)
		return (NULL);
	start = 0;
	while (s[start] && is_white(s[start], a))
		start++;
	end = (int)ft_strlen(s) - 1;
	while (s[end] && is_white(s[end], a) && end > (int)start)
		end--;
	str = ft_strsub(s, start, (end - start + 1));
	if (str == NULL)
		return (NULL);
	return (str);
}
