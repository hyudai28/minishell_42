/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 22:24:32 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/16 22:01:33 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_length(const char *word)
{
	char	quot;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (ft_strchr(word, '\'') == NULL && ft_strchr(word, '\"') == NULL)
		return (0);
	while (word[i + len] != '\0')
	{
		while (word[i + len] != '\0' && \
		word[i + len] != '\'' && word[i + len] != '\"')
			len++;
		if (word[i + len] == '\0')
			return (len);
		quot = word[i + len];
		i++;
		while (word[i + len] != '\0' && word[i + len] != quot)
			len++;
		i++;
	}
	return (len);
}

static void	remove_quot_copy(t_token *token, char *new)
{
	size_t	i;
	size_t	len;
	char	quot;

	i = 0;
	len = 0;
	while (token->word[i + len] != '\0')
	{
		while (token->word[i + len] != '\0' && \
		token->word[i + len] != '\'' && token->word[i + len] != '\"')
		{
			new[len] = token->word[i + len];
			len++;
		}
		if (token->word[i + len] == '\0')
			return ;
		quot = token->word[i + len];
		i++;
		while (token->word[i + len] != quot)
		{
			new[len] = token->word[i + len];
			len++;
		}
		i++;
	}
}

static int	clean_two_quot(t_token *token, t_envlist *env)
{
	char	*temp;

	if ((token->word[0] == '\'' && token->word[1] == '\'') || \
	token->word[0] == '\"' && token->word[1] == '\"')
	{
		temp = ft_strdup("");
		if (temp == NULL)
		{
			error("minishell: Cannot allocate memory", 1, env);
			return (1);
		}
		token->word = temp;
	}
	return (0);
}

int	remove_quot(t_token *token, t_envlist *env)
{
	char	*new;
	size_t	len;

	len = get_length(token->word);
	if (len == 0)
		return (clean_two_quot(token, env));
	token->word_len = len;
	new = malloc(sizeof(char) * (token->word_len + 1));
	if (new == NULL)
	{
		error("minishell: Cannot allocate memory", 1, env);
		return (1);
	}
	remove_quot_copy(token, new);
	new[len] = '\0';
	free(token->word);
	token->word = new;
	return (0);
}
