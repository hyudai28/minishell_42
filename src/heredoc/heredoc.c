/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:21:43 by hyudai            #+#    #+#             */
/*   Updated: 2022/05/19 23:41:58 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredocument(t_token *head)
{
	t_token	*token;

	token = head->next;
	while (token->type != TAIL)
	{
		if (token->type == HEREDOC)
		{
			//heredocを受け取る
			//<<を上書きする
			//token->type = NONEXPANDABLE_SQ;
			if (ft_strchr(token->next->word, '\'') ||\
			ft_strchr(token->next->word, '\"'))
				token->type = NONEXPANDABLE_SQ;
			else
				token->type = EXPANDABLE;
			//EOFを削除
			token_delone(token->next);
		}
		token = token->next;
	}
	return (0);
}