/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type_infd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 22:47:16 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 22:47:16 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*r_stdin(t_cmds *new, t_token *token)
{
	token = token->next;
	if (new->infd_type == FD_R_STDIN)
		close(new->infd);
	new->infd_type = FD_R_STDIN;
	new->infd = open(token->word, O_RDONLY);
	if (new->infd == -1)
		return (NULL);
	token = token->next;
	return (token);
}

static t_token	*heredoc(t_cmds *new, t_token *token)
{
	token = token->next;
	if (new->heredoc_str != NULL)
		free(new->heredoc_str);
	new->heredoc_str = token->word;
	token->word = NULL;
	new->infd_type = FD_HEREDOC;
	token = token->next;
	return (token);
}

t_token	*set_type_infd(t_cmds *new, t_token *token)
{
	if (new->prev->close_in == 1)
		new->infd_type = FD_RE_PIPE;
	else if (token->type == TAIL)
		return (token);
	else if (token->type == R_STDIN)
		token = r_stdin(new, token);
	else if (token->type == HEREDOC)
		token = heredoc(new, token);
	else if (new->prev->outfd_type == FD_PIPE_OUT)
		new->infd_type = FD_PIPE_IN;
	if (new->infd == -1)
		return (NULL);
	return (token);
}

// else if (new->outfd_type == FD_PIPE_OUT)
// {
// 	token = token->next;
// 	new->infd_type = FD_PIPE_IN;
// }
