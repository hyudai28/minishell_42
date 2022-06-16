/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:41:48 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/16 18:54:32 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *word, t_envlist *env)
{

	if (env->head)
		env = env->next;
	while (!env->head)
	{
		if (!ft_strncmp(word, env->key, (ft_strlen(env->key) + 1)))
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}
