/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:59:58 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 18:59:58 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_next_sq(char *word)
{
	size_t	len;

	len = 0;
	while (word[len] != '\0' && word[len] != '\'')
	{
		len++;
	}
	return (len + 1);
}

static size_t	get_env_length(char *word, t_envlist *env)
{
	size_t	tr_len;
	size_t	value_len;

	if (env->head)
		env = env->next;
	tr_len = 0;
	while (ft_isalnum(word[tr_len]) || word[tr_len] == '_')
		tr_len++;
	while (!env->head)
	{
		if (!ft_strncmp(word, env->key, tr_len))
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
	{
		if (word[env_less_len + env_len] == '\'')
			env_less_len += get_next_sq(word + env_less_len + env_len + 1);
		else if (word[env_less_len + env_len] == '$')
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
	}
	return (env_less_len);
}

static size_t	get_env_only_length(char *word, t_envlist *env)
{
	size_t	length;
	size_t	exit_status_digit;

	length = 0;
	exit_status_digit = get_exit_status_digit(env);
	while (*word != '\0')
	{
		if (*word == '\'')
			word += get_next_sq(word + 1);
		else if (*word == '$')
		{
			word++;
			if (*word == '?')
			{
				word++;
				length += exit_status_digit;
			}
			else
			{
				length += get_env_length(word, env);
				while (ft_isalnum(*word) || *word == '_')
					word++;
			}
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

	env_length = get_env_only_length(token->word, env);
	env_less_length = get_env_less_length(token->word);
	total_length = env_length + env_less_length;
	expand_word = (char *)malloc(sizeof(char) * (total_length + 1));
	if (expand_word == NULL)
		return (1);
	expand_word[total_length] = '\0';
	expand_word = expansion_line(expand_word, token->word, env);
	free(token->word);
	token->word = expand_word;
	token->word_len = ft_strlen(expand_word);
	return (0);
}