/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:59:58 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/16 19:23:34 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_env_length(char *word, t_envlist *env)
{
	size_t	value_len;

	if (env->head)
		env = env->next;
	while (!env->head)
	{
		if (!ft_strncmp(word, env->key, (ft_strlen(env->key) + 1)))
		{
			if (env->value == NULL)
				return (0);
			value_len = ft_strlen(env->value);
			return (value_len);
		}
		env = env->next;
	}
	return (0);
}

static size_t	get_env_less_length(char *word)
{
	size_t	env_less_len;
	size_t	env_len;

	env_less_len = 0;
	env_len = 0;
	while (word[env_less_len + env_len] != '\0')
		if (word[env_less_len + env_len] == '\'')
			env_less_len += get_next_sq(word + env_less_len + env_len + 1);
	else if (word[env_less_len + env_len] == '$' && \
			word[env_less_len + env_len + 1] != '\0')
	{
		env_len++;
		if (word[env_less_len + env_len] == '?')
			env_len++;
		else
		{
			while (ft_isalnum(word[env_less_len + env_len]) || \
					word[env_less_len + env_len] == '_')
				env_len++;
		}
	}
	else
		env_less_len++;
	return (env_less_len);
}

static char	*env_length(\
size_t *length, size_t exit_status_digit, char *word, t_envlist *env)
{
	if (*word == '?')
	{
		word++;
		(*length) += exit_status_digit;
	}
	else
	{
		(*length) += get_env_length(word, env);
		while (ft_isalnum(*word) || *word == '_')
			word++;
	}
	return (word);
}

static size_t	get_env_only_length(char *word, t_envlist *env, size_t length)
{
	size_t	exit_status_digit;

	exit_status_digit = get_exit_status_digit(env);
	while (*word != '\0')
	{
		if (*word == '\'')
			word += get_next_sq(word + 1);
		else if (*word == '$' && *word + 1 != '\0')
		{
			word++;
			word = env_length(&length, exit_status_digit, word, env);
		}
		else
			word++;
	}
	return (length);
}

int	expansion_env(t_token *token, t_envlist *env)
{
	char	*expand_word;
	size_t	env_length;
	size_t	env_less_length;
	size_t	total_length;

	env_length = get_env_only_length(token->word, env, 0);
	env_less_length = get_env_less_length(token->word);
	total_length = env_length + env_less_length;
	expand_word = (char *)ft_calloc((total_length + 1), sizeof(char));
	if (expand_word == NULL)
		return (1);
	expand_word = expansion_line(expand_word, token->word, env);
	free(token->word);
	token->word = expand_word;
	token->word_len = ft_strlen(expand_word);
	return (0);
}
