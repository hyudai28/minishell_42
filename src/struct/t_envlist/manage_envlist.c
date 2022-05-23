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

void	envlist_add(char *new_line, t_envlist *prev, t_envlist *head)
{
	t_envlist	*new;

	new = (t_envlist *)malloc(sizeof(t_envlist));
	//失敗ケア
	ft_memset(new, 0, sizeof(t_envlist));
	new->prev = prev;
	new->next = head;
	new->head = 0;
	new->doller_ret = 0;
	envlist_set_keyvalue(new, new_line);
	prev->next = new;
	head->prev = new;
}

t_envlist	*envlist_search(char *tr_line, t_envlist	*node)
{
	size_t	tr_len;

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
