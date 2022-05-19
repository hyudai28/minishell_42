/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:02:12 by hyudai            #+#    #+#             */
/*   Updated: 2022/05/19 23:17:08 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_delone(t_token *token)
{
	t_token	*before;
	t_token	*after;

	if (token->head != 1)
		before = token->prev;
	else
		return (1);
	if (token->type != TAIL)
		after = token->next;
	else
		return (1);
	if (token->word)
	{
		free(token->word);
		token->word = NULL;
	}
	free(token);
	token = NULL;
	before->next = after;
	after->prev = before;
	return (0);
}