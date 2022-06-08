/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:49:53 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/08 22:23:15 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cmds.h"

t_cmds	*cmds_constructor(int head, t_cmds *cmd_head, t_cmds *now)
{
	t_cmds	*new;

	new = (t_cmds *)malloc(sizeof(t_cmds));
	//malloc失敗処理
	ft_memset(new, 0, sizeof(t_cmds));
	new->prev = NULL;
	if (head)
	{
		new->next = NULL;
		new->head = 1;
	}
	else
	{
		new->next = cmd_head;
		new->head = 0;
		new->prev = now;
		now->next = new;
		cmd_head->prev = new;
	}
	new->infd_type = FD_STDIN;
	new->outfd_type = FD_STDOUT;
	new->cmd = NULL;
	new->heredoc_str = NULL;
	return (new);
}

void	cmds_destructor(t_cmds *cmds)
{
	int		i;
	t_cmds	*tmp;

	cmds = cmds->next;
	while (cmds->head != 1)
	{
		i = 0;
		while (cmds->cmd[i] != NULL)
		{
			free(cmds->cmd[i]);
			cmds->cmd[i] = NULL;
			i++;
		}
		free(cmds->cmd);
		cmds->cmd = NULL;
		tmp = cmds;
		cmds = cmds->next;
		free(tmp);
		tmp = NULL;
	}
	free(cmds);
	cmds = NULL;
}

t_cmds	*token_to_cmds(t_token *token)
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
		if (new == NULL)
		{
			cmds_destructor(head);
			token_destructor(token_head);
			return (NULL);
		}
		now = now->next;
		token = cmds_set_fd(new, token);
		if (token == NULL)
		{
			cmds_destructor(head);
			token_destructor(token_head);
			return (NULL);
		}
		if (!token)
			return (NULL);
	}
	return (head);
}
