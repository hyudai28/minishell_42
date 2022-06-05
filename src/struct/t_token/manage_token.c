/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_manage.c                                    :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:02:12 by hyudai            #+#    #+#             */
/*   Updated: 2022/05/23 22:28:10 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(void)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_token));
	return (new);
}

t_token	*add_token_last(t_token *head, t_token *cur)
{
	t_token	*tail;
	t_token	*last;

	tail = head->prev;
	last = tail->prev;
	last->next = cur;
	cur->prev = last;
	cur->next = tail;
	tail->prev = cur;
	return (cur);
}

t_token	*add_one(t_token *now, char **str)
{
	t_token	*after;
	t_token	*new;
	char	*add_str;

	after = now->next;
	add_str = ft_strdup(*str);
	if (!add_str)
		return (NULL);
	// new = new_token(now, &add_str);
	if (!new)
		return (NULL);
	new->next = after;
	if (after)
		after->prev = new;
	return (new);
}

int	token_delone(t_token *token)
{
	t_token	*before;
	t_token	*after;

	if (token->type != HEAD)
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
