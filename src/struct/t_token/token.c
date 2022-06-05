/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:49:47 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/05 18:15:00 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_token.h"

t_token	*token_constructor(void)
{
	t_token	*head;
	t_token	*tail;

	head = (t_token *)malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	tail = (t_token *)malloc(sizeof(t_token));
	if (!tail)
	{
		free(head);
		return (NULL);
	}
	ft_memset(head, 0, sizeof(t_token));
	ft_memset(tail, 0, sizeof(t_token));
	head->next = tail;
	tail->next = NULL;
	head->prev = NULL;
	tail->prev = head;
	head->type = HEAD;
	tail->type = TAIL;
	head->word = NULL;
	tail->word = NULL;
	head->head = 1;
	tail->head = 0;
	return (head);
}

t_token	*end_token(t_token *cur)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_token));
	new->type = TAIL;
	cur->next = new;
	new->prev = cur;
	return (new);
}

void	token_destructor(t_token *token)
{
	t_token	*tmp;

	while (token->type != TAIL)
	{
		if (token->word)
		{
			free(token->word);
			token->word = NULL;
		}
		tmp = token;
		token = token->next;
		free(tmp);
		tmp = NULL;
	}
	free(token);
	token = NULL;
}

int	token_check_separate(enum e_token_type type)
{
	if (type == TAIL)
		return (2);
	if (type == PIPE || type == REDIRECT || type == R_STDIN || \
		type == APPEND_REDIRECT || type == HEREDOC)
		return (1);
	return (0);
}
