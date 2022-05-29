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

t_token	*cmds_set_fd(t_cmds *new, t_token *token)
{
	if (new->prev->outfd_type == FD_PIPE_OUT)
		new->infd_type = FD_PIPE_IN;
	else if (token->next->type == R_STDIN)
		new->infd_type = FD_R_STDIN;
	else if (token->next->type == HEREDOC)
		new->infd_type = FD_HEREDOC;
	if (token->next->type == PIPE)
		new->outfd_type = FD_PIPE_OUT;
	else if (token->next->type == REDIRECT)
		new->outfd_type = FD_REDIRECT;
	else if (token->next->type == APPEND_REDIRECT)
		new->outfd_type = FD_APPEND_REDIRECT;
	else
		new->outfd_type = FD_STDOUT;
	return (token->next);
}
