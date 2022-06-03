/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:21:43 by hyudai            #+#    #+#             */
/*   Updated: 2022/06/04 01:00:49 by mfujishi         ###   ########.fr       */
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
			break ;
		if (ft_strncmp(new_line, dlmt, dlmt_l) == 0)
			break ;
		*line = ft_strjoin3(*line, "\n", new_line, 0); //malloc失敗
		free(temp);
		free(new_line);
	}
	free(new_line);
	return (0);
};

int	get_heredoc(t_token *token, char *delimiter)
{
	char	*line;
	size_t	delimiter_length;

	delimiter_length = ft_strlen(delimiter);
	line = readline("> "); //malloc失敗
	if (line == NULL) //error
		return (2);
	if (ft_strncmp(line, delimiter, delimiter_length) == 0)
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

static int	heredoc_expansion(t_token *token, t_envlist *env)
{
	size_t	tword_i;
	size_t	tword_len;
	size_t	envlen;

	tword_i = 0;
	tword_len = ft_strlen(token->word);
	while (token->word && tword_i < tword_len)
	{
		if (token->word[tword_i] == '$')
			if (token->word[tword_i + 1] == '?')
				tword_i = assign_var(token, env, tword_i, \
				ft_itoa(env->doller_ret));
		else
		{
				envlen = get_envlen(token->word + tword_i + 1);
				tword_i = assign_var(token, env, tword_i, \
				ft_substr(token->word, tword_i + 1, envlen));
				tword_i++;
		}
		else
			tword_i++;
		if (tword_i > tword_len)
			tword_len = ft_strlen(token->word);
	}
	return (0);
}

int	heredocument(t_token *head, t_envlist *env)
{
	t_token	*token;
	int		expandable;

	token = head->next;
	while (token->type != TAIL)
	{
		expandable = 1;
		if (token->type == HEREDOC)
		{
			if (ft_strchr(token->next->word, '\'') != NULL || \
				ft_strchr(token->next->word, '\"') != NULL)
				expandable = 0;
			if (remove_quot(token->next) != 0)
				return (1);
			if (get_heredoc(token, token->next->word) != 0)
				return (1);
			if (expandable == 1)
				heredoc_expansion(token->next, env);
			token->word_len = ft_strlen(token->word);
			token->type = HEREDOC;
		}
		token = token->next;
	}
	return (0);
}
