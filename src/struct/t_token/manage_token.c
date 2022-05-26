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

t_token	*new_token(t_token *cur, char **str)
{
	t_token	*new;

	if (**str == '\0')
		return (cur);
	new = (t_token *)malloc(sizeof(t_token));//失敗
	ft_memset(new, 0, sizeof(t_token));
	cur->next = new;
	new->prev = cur;
	get_token(new, *str);
	new->word = (char *)malloc(new->word_len + 1);//失敗
	ft_strlcpy(new->word, *str, new->word_len + 1);
	if (new->word_len == WORD_LEN_ERROR)
		return (new);
	(*str) += (new->word_len);
	new->head = 0;
	return (new);
}

t_token	*end_token(t_token *cur)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	ft_memset(new, 0, sizeof(t_token));
	new->type = TAIL;
	cur->next = new;
	new->prev = cur;
	return (new);
}

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
