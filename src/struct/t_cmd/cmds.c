/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:49:53 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/19 13:50:40 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cmds.h"

t_cmds	*cmds_constructor(int head, t_cmds *cmd_head, t_cmds *now)
{
	t_cmds	*new;

	new = (t_cmds *)malloc(sizeof(t_cmds));
	if (new == NULL)
	{
		ft_putendl_fd("minishell: Cannot allocate memory", 2);
		return (NULL);
	}
	ft_memset(new, 0, sizeof(t_cmds));
	if (head)
		new->head = 1;
	else
	{
		new->next = cmd_head;
		new->prev = now;
		now->next = new;
		cmd_head->prev = new;
	}
	new->pid = -1;
	new->infd_type = FD_STDIN;
	new->outfd_type = FD_STDOUT;
	return (new);
}

static void	cmd_free(t_cmds *cmd)
{
	size_t	i;

	i = 0;
	while (cmd->cmd[i] != NULL)
	{
		free(cmd->cmd[i]);
		cmd->cmd[i] = NULL;
		i++;
	}
}

void	cmds_destructor(t_cmds *cmds)
{
	t_cmds	*tmp;

	if (cmds->next == NULL)
		free(cmds);
	else
	{
		cmds = cmds->next;
		while (cmds->head != 1)
		{
			cmd_free(cmds);
			free(cmds->cmd);
			free(cmds->heredoc_str);
			cmds->cmd = NULL;
			tmp = cmds;
			cmds = cmds->next;
			free(tmp);
			tmp = NULL;
		}
		free(cmds);
	}
}
