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
//ここでmallocするのが理想

int	envlist_set_key(t_envlist *target, char *new_line, size_t key_length)
{
	char	*chr_pt;
	size_t	new_line_length;

	new_line_length = ft_strlen(new_line);
	target->key = ft_substr(new_line, 0, key_length);
	if (!target->key)
		return (1);
	return (0);
}

int	envlist_set_value(t_envlist *target, char *value_line)
{
	char	*chr_pt;
	size_t	key_length;

	key_length = ft_strlen(value_line);
	if (target->value)
		free(target->value);
	if (key_length == 0)
	{
		target->value = (char *)malloc(1);
		if (!target->value)
			return (1);
		target->value[0] = '\0';
		return (0);
	}
	target->value = ft_strdup(value_line);
	if (!target->value)
		return (1);
	return (0);
}

int	envlist_set_keyvalue(t_envlist *target, char *new_line)
{
	char	*chr_pt;

	chr_pt = ft_strchr(new_line, '=');
	if (!chr_pt)
	{
		target->key = ft_strdup(new_line);
		if (!target->key)
			return (1);
		target->value = NULL;
		return (0);
	}
	else
	{
		if (envlist_set_key(target, new_line, chr_pt - new_line))
			return (1);
		if (envlist_set_value(target, chr_pt + 1))
			return (1);
	}
	return (0);
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

char	*envlist_get_env(t_envlist *env, char *key)
{
	key = token_strjoin(key, " ");
	if (!key)
		return (NULL);
	key = token_strjoin(key, env->key);
	if (!key)
		return (NULL);
	return (key);
}

char	**envlist_to_key(t_envlist *head)
{
	t_envlist	*tmp;
	char		*key;
	char		**split;

	if (!head->next)
		return (NULL);
	tmp = head->next;
	key =	NULL;
	while (!tmp->head)
	{
		key = envlist_get_env(tmp, key);
		if (!key)
		{
			break ;
		}
		tmp = tmp->next;
	}
	split = ft_split(key, ' ');
	if (split == NULL)
		return (NULL);
	free(key);
	key = NULL;
	return (split);
}

char	*envlist_get_key(char *line)
{
	char	*str_key;
	char	*tmp;

	str_key = ft_strdup(line);
	if (!str_key)
		return (NULL);
	tmp = ft_strchr(str_key, '=');
	*tmp = '\0';
	return (str_key);
}