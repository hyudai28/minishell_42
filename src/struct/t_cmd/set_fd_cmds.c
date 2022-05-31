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

static	t_token	*set_type_infd(t_cmds *new, t_token *token)
{
	if (token->type == R_STDIN)
	{
		token = token->next;
		new->infd_type = FD_R_STDIN;
		new->infd = open(token->word, O_RDONLY);
		token = token->next;
	}
	else if (new->outfd_type == FD_PIPE_OUT)
	{
		token = token->next;
		new->infd_type = FD_PIPE_IN;
		token = token->next;
	}
	else if (token->type == HEREDOC)
	{
		token = token->next;
		new->infd_type = HEREDOC;
		token = token->next;
	}
	if (new->infd == -1)
		return (NULL);
	return (token);
}

static	t_token	*set_type_outfd(t_cmds *new, t_token *token)
{
	if (token->type == REDIRECT)
	{
		token = token->next;
		new->outfd_type = FD_REDIRECT;
		new->outfd = open(token->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		token = token->next;
	}
	else if (token->type == PIPE)
	{
		token = token->next;
		new->outfd_type = FD_PIPE_OUT;
		token = token->next;
	}
	else if (token->type == APPEND_REDIRECT)
	{
		token = token->next;
		new->outfd_type = FD_REDIRECT;
		new->outfd = open(token->word, O_WRONLY | O_APPEND | O_CREAT, 0644); //open err
		token = token->next;
	}
	if (new->outfd == -1)
		return (NULL);
	return (token);
}

t_token	*cmds_set_fd(t_cmds *new, t_token *token)
{
	if (token->type == TAIL)
		return (token);
	token = set_type_infd(new, token);
	if (!token)
		return (NULL);
	token = set_type_outfd(new, token);
	if (!token)
		return (NULL);
	return (token);
}
