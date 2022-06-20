/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:49:54 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/20 17:57:48 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_envlist.h"

t_envlist	*failed_envlist(t_envlist *head)
{
	ft_putendl_fd("minishell: Cannot allocate memory", 2);
	envlist_destructor(head);
	exit (1);
}

t_envlist	*make_min(t_envlist *head)
{
	t_envlist	*new;
	char		*pwd;
	char		*cwd;

	new = head;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (failed_envlist(head));
	pwd = ft_strjoin("PWD=", cwd);
	free(cwd);
	if (!pwd)
		return (failed_envlist(head));
	if (envlist_add(pwd, new, head))
		return (failed_envlist(head));
	free(pwd);
	new = new->next;
	if (envlist_add("OLDPWD", new, head))
		return (failed_envlist(head));
	new = new->next;
	if (envlist_add("SHLVL=1", new, head))
		return (failed_envlist(head));
	return (new->next);
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
	env_i = 0;
	head = new;
	new = make_min(head);
	while (envp[env_i])
	{
		if (envlist_add(envp[env_i], new, head))
		{
			envlist_destructor(head);
			return (NULL);
		}
		env_i++;
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
