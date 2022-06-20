/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 18:16:37 by hyudai            #+#    #+#             */
/*   Updated: 2022/06/20 21:38:39 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_envlist.h"
t_envlist	*failed_envlist(t_envlist *head);

int	export_change(char *new_line, t_envlist *prev, t_envlist *head);

t_envlist	*envlist_new(void)
{
	t_envlist	*new;

	new = (t_envlist *)malloc(sizeof(t_envlist));
	if (new == NULL)
		return (NULL);
	ft_memset(new, 0, sizeof(t_envlist));
	return (new);
}

int	envlist_link_list(t_envlist *new, t_envlist *prev, t_envlist *head)
{
	new->prev = prev;
	new->next = head;
	if (prev)
		prev->next = new;
	else
		head->next = new;
	head->prev = new;
	return (0);
}

int	envlist_update(char *new_line, t_envlist *prev, t_envlist *head)
{
	t_envlist	*env;
	char		*chr_pt;
	char		*str_key;

	(void)prev;
	chr_pt = ft_strchr(new_line, '=');
	if (!chr_pt)
		return (0);
	else
	{
		str_key = envlist_get_key(new_line);
		if (!str_key)
			return (1);
		env = envlist_search(str_key, head);
		free(str_key);
		str_key = NULL;
		if (!env)
			return (2);
		else if (envlist_set_value(env, chr_pt + 1))
			failed_envlist(head);
		return (1);
	}
	return (0);
}

int	envlist_add_change(char *new_line, t_envlist *prev, t_envlist *head)
{
	t_envlist	*new;
	int			change_ret;

	change_ret = envlist_update(new_line, prev, head);
	if (change_ret == 1)
		return (2);
	if (change_ret == 2)
	{
		new = envlist_new();
		if (!new)
			return (1);
		if (envlist_set_keyvalue(new, new_line))
			return (1);
		envlist_link_list(new, prev, head);
		return (0);
	}
	return (1);
}

int	envlist_add(char *new_line, t_envlist *prev, t_envlist *head)
{
	t_envlist	*new;

	new = envlist_new();
	if (!new)
		return (1);
	if (envlist_set_keyvalue(new, new_line))
		return (1);
	envlist_link_list(new, prev, head);
	return (0);
}
