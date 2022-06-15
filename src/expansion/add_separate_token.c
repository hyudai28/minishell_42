/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_separate_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 22:24:13 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 22:24:13 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_single_quot(char *word, size_t *i)
{
	*i = 0;
	while (word[*i] != '\0' && word[*i] != ' ')
	{
		if (word[*i] == '\'')
		{
			(*i)++;
			while (word[*i] != '\0' && word[*i] != '\'')
				(*i)++;
		}
		else if (word[*i] == '\"')
		{
			(*i)++;
			while (word[*i] != '\0' && word[*i] != '\"')
				(*i)++;
		}
		if (word[*i] == '\0' || word[*i] == ' ')
			return ;
		(*i)++;
	}
}

static char	*get_left(t_token *token, t_envlist *env, size_t i, t_token *new)
{
	char	*left;

	left = ft_substr(token->word, 0, i);
	if (left == NULL)
	{
		free(new);
		error("minishell: Cannot allocate memory", 1, env);
		return (NULL);
	}
	token->word = left;
	return (left);
}

static char	*get_right(t_token *new, t_envlist *env, size_t i, char *left)
{
	char	*right;

	while (new->word[i] == ' ')
		i++;
	right = ft_substr(new->word, i, ft_strlen(new->word + i));
	if (right == NULL)
	{
		free(new);
		free(left);
		error("minishell: Cannot allocate memory", 1, env);
		return (NULL);
	}
	free(new->word);
	new->word = right;
	new->type = EXPANDABLE;
	new->word_len = ft_strlen(new->word);
	return (right);
}

static t_token	*get_newtoken(t_envlist *env)
{
	t_token	*new;

	new = new_token();
	if (new == NULL)
	{
		error("minishell: Cannot allocate memory", 1, env);
		return (NULL);
	}
	return (new);
}

int	add_separate_token(t_token *token, t_envlist *env)
{
	size_t	i;
	char	*left;
	char	*right;
	t_token	*new;

	skip_single_quot(token->word, &i);
	if (token->word[i] == '\0')
		return (0);
	new = get_newtoken(env);
	if (new == NULL)
		return (1);
	new->word = token->word;
	left = get_left(token, env, i, new);
	if (left == NULL)
		return (1);
	right = get_right(new, env, i, left);
	if (right == NULL)
	{
		free(token);
		return (1);
	}
	add_token_next(token, new, token->next);
	return (0);
}
