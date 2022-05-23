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

static enum e_cmds_out_fd	cmds_set_outfd(enum e_token_type type)
{
	if (type == PIPE)
		return (C_PIPE);
	if (type == REDIRECT)
		return (C_REDIRECT);
	return (C_STDOUT);
}

static enum e_cmds_out_fd	cmds_set_infd(enum e_token_type type)
{
	if (type == PIPE)
		return (IN_PIPE);
	if (type == R_STDIN)
		return (IN_REDIRECT);
	return (C_STDOUT);
}

t_token	*cmds_set_fd(t_cmds *new, t_token *token)
{
	if (token->type == PIPE || token->type == REDIRECT)
	{
		new->outfd_type = cmds_set_outfd(token->type);
		token = token->next;
	}
	else if (token->prev->type == PIPE || token->type == R_STDIN)
	{
		if (token->type == R_STDIN)
			new->outfd_type = cmds_set_infd(token->type);
		else
			new->outfd_type = cmds_set_infd(token->prev->type);
		token = token->next;
	}
	return (token);
}
