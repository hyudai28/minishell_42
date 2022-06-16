/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 01:38:44 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/16 22:58:12 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expansion_token(t_token *token, t_envlist *env)
{
	if (expansion_env(token, env) == 1)
	{
		ft_putendl_fd("minishell: Cannot allocate memory", 2);
		return (1);
	}
	if (token->word == NULL)
		return (1);
	if (add_separate_token(token, env) == 1)
	{
		return (1);
	}
	if (remove_quot(token, env) == 1)
	{
		return (1);
	}
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
		if (expansion_token(token, env) == 1)
		{
			token_destructor(head);
			return (1);
		}
		token = token->next;
	}
	return (0);
}
