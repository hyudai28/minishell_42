/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 01:38:44 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/06 23:29:52 by mfujishi         ###   ########.fr       */
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
		quot = word[i + len];
		i++;
		while (word[i + len] != quot)
			len++;
		i++;
	}
	return (len);
}

int	remove_quot(t_token *token)
{
	char	*new;
	char	quot;
	size_t	i;
	size_t	len;

	len = get_length(token->word);
	if (len == 0)
		return (0);
	token->word_len = len;
	new = malloc(sizeof(char) * token->word_len + 1);//malloc
	if (new == NULL)
		return (1);
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
		quot = token->word[i + len];
		i++;
		while (token->word[i + len] != quot)
		{
			new[len] = token->word[i + len];
			len++;
		}
		i++;
	}
	new[len] = '\0';
	free(token->word);
	token->word = new;
	return (0);
}

static void	split_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

int	add_separate_token(t_token *token)
{
	size_t	i;
	char	*left;
	char	*right;
	t_token	*new;

	i = 0;
	while (token->word[i] != '\0' && token->word[i] != ' ')
	{
		if (token->word[i] == '\'')
		{
			i++;
			while (token->word[i] != '\0' && token->word[i] != '\'')
				i++;
		}
		i++;
	}
	if (token->word[i] == '\0')
		return (0);
	left = ft_substr(token->word, 0, i);
	if (left == NULL)
		return (1);
	while (token->word[i] == ' ')
		i++;
	right = ft_substr(token->word, i, ft_strlen(token->word + i));
	if (right == NULL)
	{
		free(left);
		return (1);
	}
	new = new_token();
	if (new == NULL)
	{
		free(right);
		free(left);
		return (1);
	}
	new->word = right;
	new->type = EXPANDABLE;
	new->word_len =	ft_strlen(new->word);
	free(token->word);
	token->word = left;
	add_token_next(token, new, token->next);
	return (0);
}

int	expansion(t_token *token, t_envlist *env)
{
	t_token	*head;

	head = token;
	token = token->next;
	while (token->type != TAIL)
	{
		if (token->type == HEREDOC)
		{
			token = token->next->next;
			continue ;
		}
		if (expansion_env(token, env) == 1)
		{
			token_destructor(token);
			return (1);
		}
		if (add_separate_token(token) == 1)
		{
			token_destructor(token);
			return (1);
		}
		if (remove_quot(token) == 1)
		{
			token_destructor(token);
			return (1);
		}
		token = token->next;
	}
	return (0);
}
