/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:49:54 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/05 18:49:28 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_envlist.h"

t_envlist	*envlist_constructor(char **envp)
{
	t_envlist	*new;
	t_envlist	*head;
	int			env_i;

	new = (t_envlist *)malloc(sizeof(t_envlist));
	//失敗ケア
	ft_memset(new, 0, sizeof(t_envlist));
	new->prev = NULL;
	new->next = NULL;
	new->head = 1;
	new->doller_ret = 0;
	new->key = NULL;
	new->value = NULL;
	env_i = -1;
	head = new;
	while (envp[++env_i])
	{
		envlist_add(envp[env_i], new, head);
		new = new->next;
	}
	return (head);
}

void	envlist_destructor(t_envlist *envlist)
{
	t_envlist	*tmp;

	envlist = envlist->next;
	while (envlist->head != 1)
	{
		free(envlist->key);
		envlist->key = NULL;
		free(envlist->value);
		envlist->value = NULL;
		tmp = envlist;
		envlist = envlist->next;
		free(tmp);
		tmp = NULL;
	}
	free(envlist);
	envlist = NULL;
}

void	envlist_show(t_envlist *env)
{
	int	i;

	i = 0;
	if (env->head)
		env = env->next;
	while (!env->head)
	{
		printf("i=[%d] key=[%s], value=[%s]\n", i++, env->key, env->value);
		env = env->next;
	}
}
