/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:06:39 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 21:06:39 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cat_no_env(\
char *expand_word, size_t *expand_word_i, char *word, size_t *word_i)
{
	if (word[*word_i] == '\'')
	{
		expand_word[*expand_word_i] = word[*word_i];
		(*expand_word_i)++;
		(*word_i)++;
		while (word[*word_i] != '\0' && word[*word_i] != '\'')
		{
			expand_word[*expand_word_i] = word[*word_i];
			(*expand_word_i)++;
			(*word_i)++;
		}
	}
	expand_word[*expand_word_i] = word[*word_i];
	(*expand_word_i)++;
	(*word_i)++;
}

static size_t	cat_exit_status(
	char *expand_word, t_envlist *env, size_t exit_status_len, size_t *word_i)
{
	size_t	i;
	int		exit_status;

	i = ft_strlen(expand_word);
	exit_status = env->doller_ret;
	(*word_i)++;
	if (exit_status == 0)
	{
		expand_word[i] = '0';
		expand_word[i + 1] = '\0';
		return (0);
	}
	expand_word[i + exit_status_len] = '\0';
	exit_status_len--;
	while (exit_status != 0)
	{
		expand_word[i + exit_status_len] = exit_status % 10 + '0';
		exit_status = exit_status / 10;
		exit_status_len--;
	}
	return (exit_status_len);
}

static void	cat_env(\
char *expand_word, size_t *expand_word_i, char *word, t_envlist *env)
{
	char	*env_word;
	size_t	env_word_i;

	env_word = get_env_value(word, env);
	if (env_word == NULL)
		return ;
	env_word_i = 0;
	while (env_word[env_word_i] != '\0')
	{
		expand_word[*expand_word_i] = env_word[env_word_i];
		(*expand_word_i)++;
		env_word_i++;
	}
}

char	*expansion_line(char *expand_word, char *word, t_envlist *env)
{
	size_t	expand_word_i;
	size_t	word_i;
	size_t	exit_status_length;

	expand_word_i = 0;
	word_i = 0;
	exit_status_length = get_exit_status_digit(env);
	while (word[word_i] != '\0')
		if (word[word_i] != '$')
			cat_no_env(expand_word, &expand_word_i, word, &word_i);
	else
	{
		word_i++;
		if (word[word_i] == '?')
			expand_word_i += cat_exit_status(\
				expand_word, env, exit_status_length, &word_i);
		else
		{
			cat_env(expand_word, &expand_word_i, word + word_i, env);
			while (ft_isalnum(word[word_i]) || word[word_i] == '_')
				word_i++;
		}
	}
	return (expand_word);
}
