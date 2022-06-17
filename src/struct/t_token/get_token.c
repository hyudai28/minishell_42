/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:50:40 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/17 18:13:25 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_token.h"

static size_t	is_separate_char(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else if (c == ' ')
		return (3);
	else if (c == '<')
		return (4);
	else if (c == '>')
		return (5);
	else if (c == '|')
		return (6);
	return (0);
}

static void	get_normal(char *str, t_token *new)
{
	size_t	len;
	size_t	str_len;
	char	quot;

	len = 0;
	str_len = ft_strlen(str);
	while (len < str_len && !ft_isspace(str[len]))
	{
		if (is_separate_char(str[len]) >= 3)
			break ;
		while (len < str_len && is_separate_char(str[len]) == 0)
			len++;
		if (is_separate_char(str[len]) >= 3 || str[len] == '\0')
			break ;
		quot = str[len];
		len++;
		while (len < str_len && str[len] != quot)
			len++;
		len++;
		if (len > str_len)
			len = str_len;
	}
	new->word_len = len;
	new->type = EXPANDABLE;
}

static void	get_redirect(char *str, t_token *new)
{
	if (!ft_strncmp(str, ">>", 2))
	{
		new->word_len = 2;
		new->type = APPEND_REDIRECT;
	}
	else if (!ft_strncmp(str, ">", 1))
	{
		new->word_len = 1;
		new->type = REDIRECT;
	}
	else if (!ft_strncmp(str, "<<", 2))
	{
		new->word_len = 2;
		new->type = HEREDOC;
	}
	else if (!ft_strncmp(str, "<", 1))
	{
		new->word_len = 1;
		new->type = R_STDIN;
	}
}

static void	get_pipe(t_token *new)
{
	new->word_len = 1;
	new->type = PIPE;
}

void	get_token(t_token *new, char *str)
{
	if (*str == '|')
		get_pipe(new);
	else if (*str == '<' || *str == '>')
		get_redirect(str, new);
	else
		get_normal(str, new);
}
