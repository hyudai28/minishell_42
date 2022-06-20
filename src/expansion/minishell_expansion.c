/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 01:38:44 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/20 15:47:27 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_doller(t_token *token)
{
	if (!ft_strncmp(token->word, "$", 2))
		return (0);
	else if (token->word[0] == '$' && token->word[1] == '$')
	{
		free(token->word);
		token->word = NULL;
		token->word = ft_strdup("");
		if (token->word == NULL)
		{
			ft_putendl_fd("minishell: Cannot allocate memory", 2);
			return (1);
		}
		return (0);
	}
	return (2);
}

static int	expansion_error(t_token *token)
{
	if (token_check_separate(token->prev->type) == 1 && \
		token->prev->type != PIPE)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->word, 2);
		ft_putendl_fd(": ambiguous redirect", 2);
		return (1);
	}
	else if (token->prev->type == HEAD && token->next->type == TAIL)
		return (1);
	else
		return (2);
}

int	expansion_token(t_token *token, t_envlist *env)
{
	int		ret;

	ret = check_doller(token);
	if (ret != 2)
		return (ret);
	ret = expansion_env(token, env);
	if (ret != 0)
	{
		if (ret == 1)
			return (1);
		return (expansion_error(token));
	}
	if (add_separate_token(token, env) == 1)
		return (1);
	if (remove_quot(token, env) == 1)
		return (1);
	return (0);
}

int	expansion(t_token *token, t_envlist *env)
{
	t_token	*head;
	int		ret;

	head = token;
	token = token->next;
	while (token->type != TAIL)
	{
		if (token->type == HEREDOC)
		{
			token = token->next->next;
			continue ;
		}
		ret = expansion_token(token, env);
		if (ret == 1)
		{
			token_destructor(head);
			return (1);
		}
		token = token->next;
		if (ret == 2)
			token_delone(token->prev);
	}
	return (0);
}
