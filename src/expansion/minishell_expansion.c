/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 01:38:44 by mfujishi          #+#    #+#             */
/*   Updated: 2022/05/27 22:32:02 by hyudai           ###   ########.fr       */
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

static int	remove_quot(t_token *token)
{
	char	*new;
	char	quot;
	size_t	i;
	size_t	len;

	len = get_length(token->word);
	if (len == 0)
		return (0);
	new = malloc(sizeof(char) * len + 1);//malloc
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

int	expansion(t_token *token, t_envlist *env)
{
	t_token	*head;

	head = token;
	token = token->next;
	while (token->type != TAIL)
	{
		expansion_dq(token, env);
		token = token->next;
	}
	token = head->next;
	while (token->type != TAIL)
	{
		remove_quot(token);
		token = token->next;
	}
	return (0);
}
