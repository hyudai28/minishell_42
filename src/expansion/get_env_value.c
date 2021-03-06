/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:41:48 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/16 21:21:59 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *word, t_envlist *env)
{
	size_t	tr_len;

	if (env->head)
		env = env->next;
	tr_len = 0;
	while (ft_isalnum(word[tr_len]) || word[tr_len] == '_')
		tr_len++;
	while (!env->head)
	{
		if (ft_strlen(env->key) <= tr_len && \
				!ft_strncmp(word, env->key, tr_len))
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}
