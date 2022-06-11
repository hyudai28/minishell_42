/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:49:54 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 23:41:51 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_envlist.h"

t_envlist	*envlist_constructor(char **envp)
{
	t_envlist	*new;
	t_envlist	*head;
	int			env_i;

	new = (t_envlist *)malloc(sizeof(t_envlist));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_envlist));
	new->head = 1;
	env_i = -1;
	head = new;
	while (envp[++env_i])
	{
		if (envlist_add(envp[env_i], new, head))
		{
			envlist_destructor(head);
			return (NULL);
		}
		new = new->next;
	}
	return (head);
}

void	envlist_destructor(t_envlist *envlist)
{
	t_envlist	*tmp;

	if (!envlist)
		return ;
	else if (!envlist->next)
	{
		free(envlist);
		return ;
	}
	envlist = envlist->next;
	while (envlist->head != 1)
	{
		free(envlist->key);
		envlist->key = NULL;
		free(envlist->value);
		envlist->value = NULL;
		tmp = envlist;
		if (!envlist->next)
			break ;
		envlist = envlist->next;
		free(tmp);
		tmp = NULL;
	}
	free(envlist);
	envlist = NULL;
}
