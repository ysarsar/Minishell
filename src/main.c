/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:00:39 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/15 11:36:02 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_env **head)
{
	t_env	*cur;
	t_env	*next;

	cur = *head;
	while (cur)
	{
		next = cur->next;
		free(cur->data);
		free(cur);
		cur = next;
	}
	*head = NULL;
}

int		main(int ac, char **av, char **env)
{
	t_env	*envp;
	char	**tab;
	int		i;

	(void)ac;
	(void)av;
	i = -1;
	envp = NULL;
	signal(SIGINT, my_func);
	if (env[0] != NULL)
	{
		tab = env_to_tab(env);
		envp = my_getenv(tab);
		msh_loop(&envp);
		free_list(&envp);
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
	else
		ft_putendl("Minishell: environment not found!");
	return (0);
}

char	**env_to_tab(char **env)
{
	char	**tab;
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (!(tab = (char **)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	while (env[++i])
		tab[i] = ft_strdup(env[i]);
	tab[i] = NULL;
	return (tab);
}

t_env	*my_getenv(char **env)
{
	int		i;
	t_env	*head;
	t_env	*envp;

	envp = NULL;
	if (!(head = (t_env *)ft_memalloc(sizeof(t_env))))
		return (envp);
	head->next = NULL;
	envp = head;
	i = 0;
	while (env[i] != NULL)
	{
		envp->data = ft_strdup(env[i]);
		if (!env[i + 1])
			break ;
		if (!(envp->next = (t_env *)ft_memalloc(sizeof(t_env))))
			return (NULL);
		envp = envp->next;
		i++;
	}
	envp->next = NULL;
	return (head);
}
