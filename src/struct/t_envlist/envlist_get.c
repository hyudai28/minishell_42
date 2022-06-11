/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:37:37 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 23:37:37 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*envlist_get_env(t_envlist *env, char *key)
{
	char	*temp;

	key = token_strjoin(key, " ");
	if (!key)
		return (NULL);
	temp = key;
	key = token_strjoin(key, env->key);
	if (!key)
	{
		free(temp);
		return (NULL);
	}
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
	key = NULL;
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
