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
		if (word[*i] == '\0' || word[*i] == ' ')
			return ;
		(*i)++;
	}
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
	left = ft_substr(token->word, 0, i);
	if (left == NULL)
	{
		error("minishell: Cannot allocate memory", 1, env);
		return (1);
	}
	while (token->word[i] == ' ')
		i++;
	right = ft_substr(token->word, i, ft_strlen(token->word + i));
	if (right == NULL)
	{
		error("minishell: Cannot allocate memory", 1, env);
		free(left);
		return (1);
	}
	new = new_token();
	if (new == NULL)
	{
		error("minishell: Cannot allocate memory", 1, env);
		free(right);
		free(left);
		return (1);
	}
	new->word = right;
	new->type = EXPANDABLE;
	new->word_len = ft_strlen(new->word);
	free(token->word);
	token->word = left;
	add_token_next(token, new, token->next);
	return (0);
}
