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

static t_token	*separate_token(t_cmds *new, t_token *token, size_t *index)
{
	new->cmd[*index] = NULL;
	if (token->type != EXPANDABLE)
		return (token);
	if (token->word == NULL)
		return (token->next);
	new->cmd[*index] = ft_strdup(token->word);
	if (new->cmd[*index] == NULL)
	{
		ft_putendl_fd("minishell: Cannot allocate memory", 2);
		return (NULL);
	}
	token = token->next;
	(*index)++;
	return (token);
}

static t_token	*pipe_set_outfd(t_cmds *new, t_token *token)
{
	if (token->type != PIPE)
		return (token);
	if (new->outfd_type == FD_STDOUT)
		new->outfd_type = FD_PIPE_OUT;
	else
		new->close_in = 1;
	return (token->next);
}

t_token	*cmds_set_fd(t_cmds *new, t_token *token)
{
	t_token	*token_head;
	size_t	index;
	size_t	size;

	token_head = token;
	(void)token_head;
	index = 0;
	size = count_token(token);
	new->cmd = (char **)ft_calloc((size + 1), sizeof(char *));
	if (new->cmd == NULL)
		return (NULL);
	while (token->type != PIPE && token->type != TAIL)
	{
		token = set_type_infd(new, token);
		if (!token)
			return (NULL);
		token = set_type_outfd(new, token);
		if (!token)
			return (NULL);
		token = separate_token(new, token, &index);
		if (!token)
			return (NULL);
	}
	token = pipe_set_outfd(new, token);
	return (token);
}
