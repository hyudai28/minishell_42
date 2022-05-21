/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:21:43 by hyudai            #+#    #+#             */
/*   Updated: 2022/05/21 22:42:38 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_heredoc(t_token *token, const char *delimiter)
{
	char	*line;
	char	*new_line;
	char	*temp;
	size_t	delimiter_length;

	line = readline("> "); //malloc失敗
	delimiter_length = ft_strlen(delimiter);
	while (ft_strncmp(line, delimiter, delimiter_length + 1) != 0)
	{
		printf("[%s], [%s]\n",line, delimiter);/
		temp = line;
		new_line = readline("");
		line = ft_strjoin(line, new_line); //malloc失敗
		free(temp);
		free(new_line);
	}
	token->word = line;
	return (0);
}

int	heredocument(t_token *head)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token = head->next;
	while (token->type != TAIL)
	{
		if (token->type == HEREDOC)
		{
			read_heredoc(token, "EOF");
			printf("%s\n", token->word);
			exit(0);
			//heredocを受け取る
			//<<を上書きする
			//token->type = NONEXPANDABLE_SQ;
			if (ft_strchr(token->next->word, '\'') ||\
			ft_strchr(token->next->word, '\"'))
				token->type = NONEXPANDABLE_SQ;
			else
				token->type = EXPANDABLE;
			//EOFを削除
			token_delone(token->next);
		}
		token = token->next;
	}
	return (0);
}
