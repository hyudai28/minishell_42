/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:04:46 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 23:04:46 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_to_cmds_error(void *p, t_token *token, t_cmds *cmds)
{
	if (p == NULL)
	{
		cmds_destructor(cmds);
		token_destructor(token);
		return (1);
	}
	return (0);
}

t_cmds	*token_to_cmds(t_token *token, t_envlist *env)
{
	t_cmds	*head;
	t_cmds	*new;
	t_cmds	*now;
	t_token	*token_head;

	token_head = token;
	head = cmds_constructor(TRUE, NULL, NULL);
	if (head == NULL)
	{
		token_destructor(token_head);
		return (NULL);
	}
	now = head;
	token = token->next;
	while (token->type != TAIL)
	{
		new = cmds_constructor(FALSE, head, now);
		if (token_to_cmds_error(new, token_head, head) == 1)
			return (NULL);
		now = now->next;
		token = cmds_set_fd(new, token, env);
		if (token_to_cmds_error(token, token_head, head) == 1)
			return (NULL);
	}
	return (head);
}
