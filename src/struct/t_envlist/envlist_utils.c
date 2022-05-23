/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:50:10 by mfujishi          #+#    #+#             */
/*   Updated: 2022/05/24 00:50:10 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_envlist.h"

void	envlist_set_keyvalue(t_envlist *target, char *new_line)
{
	int	chr;

	chr = ft_strchr_gnl(new_line, '=');
	if (chr == -1)
	{
		target->key = ft_strdup(new_line);//malloc失敗
		target->value = NULL;
		return ;
	}
	target->key = ft_substr(new_line, 0, chr);//malloc失敗
	target->value = ft_substr(new_line, chr + 1, ft_strlen(new_line) - chr);
		//malloc失敗
}

int	envlist_node_count(t_envlist *head)
{
	t_envlist	*tmp;
	int			node_count;

	if (!head)
		return (0);
	tmp = head->next;
	node_count = 0;
	while (!tmp->head)
	{
		tmp = tmp->next;
		node_count++;
	}
	return (node_count);
}

char	**envlist_to_char(t_envlist *head)
{
	t_envlist	*tmp;
	char		*key;
	char		**split;

	tmp = head->next;
	key = NULL;
	while (!tmp->head)
	{
		key = token_strjoin(key, tmp->key);//失敗
		key = token_strjoin(key, " ");
		tmp = tmp->next;
	}
	split = ft_split(key, ' ');
	free(key);
	key = NULL;
	return (split);
}
