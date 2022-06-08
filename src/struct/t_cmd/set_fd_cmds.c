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

static t_token	*set_type_infd(t_cmds *new, t_token *token)
{
	if (token->type == TAIL)
		return (token);
	if (token->type == R_STDIN)
	{
		token = token->next;
		if (new->infd_type == FD_R_STDIN)
			close(new->infd);
		new->infd_type = FD_R_STDIN;
		new->infd = open(token->word, O_RDONLY);
		if (new->infd == -1)
		{
			error("");
			exit(0);
		}
		token = token->next;
	}
	else if (new->outfd_type == FD_PIPE_OUT)
	{
		token = token->next;
		new->infd_type = FD_PIPE_IN;
	}
	else if (token->type == HEREDOC)
	{
		token = token->next;
		if (new->heredoc_str != NULL)
			free(new->heredoc_str);
		new->heredoc_str = token->word;
		token->word = NULL;
		new->infd_type = FD_HEREDOC;
		token = token->next;
	}
	if (new->infd == -1)
		return (NULL);
	return (token);
}

static t_token	*set_type_outfd(t_cmds *new, t_token *token)
{
	if (token->type == TAIL)
		return (token);
	if (token->type == REDIRECT)
	{
		token = token->next;
		if (new->outfd_type == FD_REDIRECT || new->outfd_type == FD_APPEND_REDIRECT)
			close(new->outfd);
		new->outfd_type = FD_REDIRECT;
		new->outfd = open(token->word, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		token = token->next;
	}
	else if (token->type == PIPE)
	{
		token = token->next;
		new->outfd_type = FD_PIPE_OUT;
	}
	else if (token->type == APPEND_REDIRECT)
	{
		token = token->next;
		if (new->outfd_type == FD_REDIRECT || new->outfd_type == FD_APPEND_REDIRECT)
			close(new->outfd);
		new->outfd_type = FD_REDIRECT;
		new->outfd = open(token->word, O_WRONLY | O_APPEND | O_CREAT, 0644); //open err
		token = token->next;
	}
	if (new->outfd == -1)
		return (NULL);
	return (token);
}

static t_token	*separate_token(t_cmds *new, t_token *token, size_t *index)
{
	char	**cmd;
	size_t	size;

	if (token_check_separate(token->type))
		return (token);
	size = count_token(token);
	if (token->type != EXPANDABLE)
		return (token);
	new->cmd[*index] = ft_strdup(token->word);//malloc失敗時にfree処理
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
	static int i = 0;

	token_head = token;
	index = 0;
	size = count_token(token);
	new->cmd = (char **)ft_calloc((size + 1), sizeof(char *));
	if (new->cmd == NULL)
		return (NULL);
	while (token->type != PIPE && token->type != TAIL)
	{
		token = set_type_infd(new, token); //open errorのケース
		if (!token)
			return (NULL);
		token = set_type_outfd(new, token); //open errorのケース
		if (!token)
			return (NULL);
		token = separate_token(new, token, &index);
		if (!token)
			return (NULL);
	}
	return (token);
}
