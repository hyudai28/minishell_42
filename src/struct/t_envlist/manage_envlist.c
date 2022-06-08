/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_envlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:50:44 by mfujishi          #+#    #+#             */
/*   Updated: 2022/05/24 00:50:44 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_envlist.h"

t_envlist	*envlist_new()
{
	t_envlist	*new;
	size_t		i;

	i = 0;
	new = (t_envlist *)malloc(sizeof(t_envlist));
	if (new == NULL)
		return (NULL);
	ft_memset(new, 0, sizeof(t_envlist));
	//new->head = 0;
	//new->doller_ret = 0;
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

int	envlist_add(char *new_line, t_envlist *prev, t_envlist *head)
{
	t_envlist	*new;
	size_t		i;

	i = 0;
	new = envlist_new();
	if (!new)
		return (1);
	if (envlist_set_keyvalue(new, new_line))
		return (1);
	envlist_link_list(new, prev, head);
	return (0);
}

t_envlist	*envlist_search(char *tr_line, t_envlist *head)
{
	size_t	tr_len;
	t_envlist	*node;

	node = head;
	if (node->head)
		node = node->next;
	tr_len = ft_strlen(tr_line);
	while (!node->head)
	{
		if (!ft_strncmp(tr_line, node->key, tr_len + 1))
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	envlist_delete(char *delete_line, t_envlist *head)
{
	t_envlist	*target;
	t_envlist	*target_prev;
	t_envlist	*target_next;

	target = envlist_search(delete_line, head);
	if (!target)
		return ;
	target_next = target->next;
	target_prev = target->prev;
	target_prev->next = target_next;
	target_next->prev = target_prev;
	free(target->key);
	target->key = NULL;
	free(target->value);
	target->value = NULL;
	free(target);
	target = NULL;
}
