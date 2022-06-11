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
	char	**cmd;
	size_t	size;

	if (token_check_separate(token->type))
		return (token);
	size = count_token(token);
	if (token->type != EXPANDABLE)
		return (token);
	new->cmd[*index] = ft_strdup(token->word);
	if (new->cmd[*index] == NULL)
		return (NULL);
	token = token->next;
	(*index)++;
	return (token);
}

t_token	*cmds_set_fd(t_cmds *new, t_token *token)
{
	t_token	*token_head;
	size_t	index;
	size_t	size;

	token_head = token;
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
	return (token);
}
