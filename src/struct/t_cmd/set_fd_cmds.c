/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:50:53 by mfujishi          #+#    #+#             */
/*   Updated: 2022/05/24 00:50:53 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cmds.h"

static int	set_type_infd(t_cmds *new, t_token *token)
{
	while (token->type != PIPE && token->type != TAIL)
		token = token->next;
	while (token->type != R_STDIN && token->type != HEREDOC)
		token = token->prev;
	if (token->type == R_STDIN)
	{
		token = token->next;
		new->infd_type = FD_R_STDIN;
		new->infd = open(token->word, O_RDONLY);
	}
	else if (new->outfd_type == FD_PIPE_OUT)
	{
		token = token->next;
		new->infd_type = FD_PIPE_IN;
	}
	else if (token->type == HEREDOC)
	{
		token = token->next;
		new->infd_type = HEREDOC;
	}
	if (new->infd == -1)
		return (1);
	return (0);
}

static int	set_type_outfd(t_cmds *new, t_token *token)
{
	while (token->type != PIPE && token->type != TAIL)
		token = token->next;
	while (token->type != REDIRECT && token->type != APPEND_REDIRECT)
		token = token->prev;
	if (token->type == REDIRECT)
	{
		token = token->next;
		new->outfd_type = FD_REDIRECT;
		new->outfd = open(token->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else if (token->type == PIPE)
	{
		token = token->next;
		new->outfd_type = FD_PIPE_OUT;
	}
	else if (token->type == APPEND_REDIRECT)
	{
		token = token->next;
		new->outfd_type = FD_REDIRECT;
		new->outfd = open(token->word, O_WRONLY | O_APPEND | O_CREAT, 0644); //open err
	}
	if (new->outfd == -1)
		return (1);
	return (0);
}

t_token	*cmds_set_fd(t_cmds *new, t_token *token)
{
	if (set_type_infd(new, token) == 1)
		return (NULL);
	if (set_type_outfd(new, token) == 1)
		return (NULL);
	while (token->type != PIPE && token->type != TAIL)
		token = token->next;
	if (token->type == PIPE)
	return (token);
}
