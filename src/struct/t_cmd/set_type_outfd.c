/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type_outfd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 22:58:34 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 22:58:34 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*redirect(t_cmds *new, t_token *token, t_envlist *env)
{
	token = token->next;
	if (new->outfd_type == FD_REDIRECT || \
			new->outfd_type == FD_APPEND_REDIRECT)
		close(new->outfd);
	new->outfd_type = FD_REDIRECT;
	new->outfd = open(token->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (new->outfd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->word, 2);
		ft_putstr_fd(": ", 2);
		error(strerror(errno), 1, env);
		return (token);
	}
	token = token->next;
	return (token);
}

static t_token	*append_redirect(t_cmds *new, t_token *token, t_envlist *env)
{
	token = token->next;
	if (new->outfd_type == FD_REDIRECT || \
		new->outfd_type == FD_APPEND_REDIRECT)
		close(new->outfd);
	new->outfd_type = FD_REDIRECT;
	new->outfd = open(token->word, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (new->outfd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->word, 2);
		ft_putstr_fd(": ", 2);
		error(strerror(errno), 1, env);
		return (token);
	}
	token = token->next;
	return (token);
}

t_token	*set_type_outfd(t_cmds *new, t_token *token, t_envlist *env)
{
	if (token->type == TAIL)
		return (token);
	else if (token->type == REDIRECT)
		token = redirect(new, token, env);
	else if (token->type == APPEND_REDIRECT)
		token = append_redirect(new, token, env);
	if (new->outfd == -1)
		return (NULL);
	return (token);
}

// else if (token->type == PIPE)
// {
// 	token = token->next;
// 	new->outfd_type = FD_PIPE_OUT;
// }
