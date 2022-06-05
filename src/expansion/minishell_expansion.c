/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 01:38:44 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/05 15:49:13 by hyudai           ###   ########.fr       */
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

	token->word_len = get_length(token->word);
	if (token->word_len == 0)
		return (0);
	new = malloc(sizeof(char) * token->word_len + 1);//malloc
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

//quotを見つけたら次のquotまで無視する。
static int	ft_split_count(char *s, char c)
{
	int		count;
	int		i;
	char	quout;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == '\'' || s[i] == '\"') && s[i] != '\0')
		{
			quout = s[i++];
			while (s[i] != quout && s[i] != '\0')
				i++;
			i++;
		}
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0' && !(s[i] == '\'' || s[i] == '\"'))
		{
			count++;
			while (s[i] != c && s[i] != '\0' && !(s[i] == '\'' || s[i] == '\"'))
				i++;
		}
	}
	return (count);
}

t_token	*add_separate_token(t_token *token)
{
	int		split_ct;
	int		split_i;
	char	**split_token_word;

	split_ct = ft_split_count(token->word, ' ');
	if (split_ct == 1)
		return (token);
	split_token_word = ft_split(token->word, ' ');
	if (!split_token_word)
		return (NULL);
	token->word[ft_strchr_gnl(token->word, ' ')] = '\0';
	split_i = 1;
	while (split_i < split_ct)
	{
		token = add_one(token, &split_token_word[split_i]);
		if (!token)
		{
			split_free(split_token_word);
			return (NULL);
		}
		split_i++;
	}
	split_free(split_token_word);
	return (token);
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
		expansion_dq(token, env);
		add_separate_token(token);
		token = token->next;
	}
	token = head->next;
	while (token->type != TAIL)
	{
		if (token->type == HEREDOC)
		{
			token = token->next->next;
			continue ;
		}
		remove_quot(token);
		token = token->next;
	}
	return (0);
}
