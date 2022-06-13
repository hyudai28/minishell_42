/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:21:43 by hyudai            #+#    #+#             */
/*   Updated: 2022/06/13 19:20:47 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	read_heredoc(char *dlmt, size_t dlmt_l, char **line)
{
	char	*new_line;
	char	*temp;

	while (1)
	{
		temp = *line;
		new_line = readline("> ");
		if (new_line == NULL)
		{
			write(1, "\b\b", 2);
			write(2, "minishell: warning: not found delimiter (wanted `", 49);
			ft_putstr_fd(dlmt, 2);
			write(2, "')\n", 3);
			break ;
		}
		if (ft_strncmp(new_line, dlmt, (dlmt_l + 1)) == 0)
			break ;
		*line = ft_strjoin3(*line, "\n", new_line, 0);
		free(temp);
		free(new_line);
		if (*line == NULL)
			return (1);
	}
	free(new_line);
	return (0);
}

int	get_heredoc(t_token *token, char *delimiter)
{
	char	*line;
	size_t	delimiter_length;

	delimiter_length = ft_strlen(delimiter);
	line = readline("> ");
	if (line == NULL)
	{
		write(1, "\b\b", 2);
		write(2, "minishell: warning: not found delimiter (wanted `", 49);
		ft_putstr_fd(delimiter, 2);
		write(2, "')\n", 3);
		return (1);
	}
	if (ft_strncmp(line, delimiter, (delimiter_length + 1)) == 0)
	{
		free(line);
		free(token->next->word);
		token->next->word = ft_strdup("");
		return (0);
	}
	read_heredoc(delimiter, delimiter_length, &line);
	free(token->next->word);
	token->next->word = line;
	return (0);
}

static int	parse_heredoc(t_token *token, t_envlist *env)
{
	int	expandable;

	expandable = 1;
	if (ft_strchr(token->next->word, '\'') != NULL || \
		ft_strchr(token->next->word, '\"') != NULL)
			expandable = 0;
	if (remove_quot(token->next, env) != 0)
	{
		return (1);
	}
	if (get_heredoc(token, token->next->word) != 0)
	{
		return (1);
	}
	if (expandable == 1 && heredoc_expansion(token->next, env) == 1)
		return (1);
	return (0);
}

int	heredocument(t_token *head, t_envlist *env)
{
	t_token	*token;

	token = head->next;
	while (token->type != TAIL)
	{
		if (token->type == HEREDOC)
		{
			if (parse_heredoc(token, env) == 1)
			{
				token_destructor(head);
				return (1);
			}
			token->word_len = ft_strlen(token->word);
			token->type = HEREDOC;
		}
		token = token->next;
	}
	return (0);
}
