/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:49:47 by mfujishi          #+#    #+#             */
/*   Updated: 2022/05/26 22:05:19 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_token.h"

t_token	*token_constructor(void)
{
	t_token	*head;

	head = (t_token *)malloc(sizeof(t_token));
	if (!head)
		return (NULL);
	ft_memset(head, 0, sizeof(t_token));
	head->next = NULL;
	head->prev = NULL;
	head->type = HEAD;
	head->word = NULL;
	head->head = 1;
	return (head);
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

size_t	count_token(t_token *token)
{
	size_t	size;

	size = 0;
	while (!token_check_separate(token->type))
	{
		size++;
		token = token->next;
	}
	return (size);
}

int	token_check_separate(enum e_token_type type)
{
	if (type == TAIL)
		return (2);
	if (type == PIPE || type == REDIRECT || type == R_STDIN)
		return (1);
	return (0);
}
