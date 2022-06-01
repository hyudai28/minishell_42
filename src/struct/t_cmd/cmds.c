/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:49:53 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/01 22:03:52 by mfujishi         ###   ########.fr       */
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

static t_token	*separate_token(t_cmds *new, t_token *token)
{
	char	**cmd;
	size_t	size;
	size_t	index;

	size = count_token(token);
	cmd = (char **)malloc(sizeof(char *) * (size + 1));
	if (cmd == NULL)
		return (NULL);
	index = 0;
	while (!token_check_separate(token->type))
	{
		cmd[index] = ft_strdup(token->word);//malloc失敗時にfree処理
		token = token->next;
		index++;
	}
	cmd[index] = NULL;
	new->cmd = cmd;
	return (token);
}

t_cmds	*token_to_cmds(t_token *token)
{
	t_cmds	*head;
	t_cmds	*new;
	t_cmds	*now;

	head = cmds_constructor(TRUE, NULL, NULL);
	now = head;
	token = token->next;
	while (token->type != TAIL)
	{
		new = cmds_constructor(FALSE, head, now);
		now = now->next;
		token = separate_token(new, token);
		if (token->type == TAIL)
			break ;
		token = cmds_set_fd(new, token);
		if (!token)
			return (NULL);
	}
	return (head);
}
