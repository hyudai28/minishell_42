/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:21:43 by hyudai            #+#    #+#             */
/*   Updated: 2022/05/30 02:05:54 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_heredoc(t_token *token, t_token *next, char *delimiter)
{
	char	*line;
	char	*new_line;
	char	*temp;
	size_t	delimiter_length;

	delimiter_length = ft_strlen(delimiter);
	line = readline("> "); //malloc失敗
	if (line == NULL)
		return (1);
	if (ft_strncmp(line, delimiter, delimiter_length) == 0)
		return (0);
	while (1)
	{
		temp = line;
		new_line = readline("> ");
		if (new_line == NULL)
			break ;
		// printf("[%s], [%s]\n", new_line, delimiter);
		if (ft_strncmp(new_line, delimiter, delimiter_length) == 0)
			break ;
		line = ft_strjoin3(line, "\n", new_line, 0); //malloc失敗
		free(temp);
		free(new_line);
	}
	free(new_line);
	token->next->word = line;
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
			read_heredoc(token, token->next, token->next->word);
			token->word_len = ft_strlen(token->word);
			token->type = HEREDOC;
		}
		token = token->next;
	}
	return (0);
}
