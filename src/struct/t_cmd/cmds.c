/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:49:53 by mfujishi          #+#    #+#             */
/*   Updated: 2022/05/27 23:35:09 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cmds.h"

t_cmds	*cmds_constructor(int head, t_cmds *cmd_head)
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
	}
	new->infd_type = FD_STDIN;
	new->outfd_type = FD_STDOUT;
	new->cmd = NULL;
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
		while (cmds->cmd[i])
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

	head = cmds_constructor(TRUE, NULL);
	now = head;
	token = token->next;
	while (token->type != TAIL) //ls | cat
	{
		while (token_check_separate(token->type))
			token = token->next;
		new = cmds_constructor(FALSE, head);
		new->cmd = separate_token(token);
		token = cmds_set_fd(new, token);
		while (!token_check_separate(token->type))
			token = token->next;
		new->prev = now;
		now->next = new;
		head->prev = now;
		now = now->next;
	}
	return (head);
}
