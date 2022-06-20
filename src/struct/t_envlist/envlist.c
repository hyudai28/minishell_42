/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:49:54 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/20 17:29:25 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_envlist.h"

t_envlist	*failed_envlist(t_envlist *new)
{
	envlist_destructor(new);
	return (NULL);
}

t_envlist	*envp_is_null(t_envlist *head)
{
	t_envlist	*new;
	char		*pwd;
	char		*cwd;

	new = head;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (head);
	pwd = ft_strjoin("pwd=", cwd);
	if (!pwd)
		return (failed_envlist(new));
	if (envlist_add(pwd, new, head))
		return (failed_envlist(new));
	new = new->next;
	if (envlist_add("OLDPWD", new, head))
		return (failed_envlist(new));
	new = new->next;
	if (envlist_add("SHLVL=1", new, head))
		return (failed_envlist(new));
	return (head);
}

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
	if (envp[0] == NULL)
		return (envp_is_null(head));
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
