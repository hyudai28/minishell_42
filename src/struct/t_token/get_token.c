/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:50:40 by mfujishi          #+#    #+#             */
/*   Updated: 2022/05/24 00:50:40 by mfujishi         ###   ########.fr       */
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
	size_t	c_status;
	size_t	str_len;

	len = 0;
	c_status = 0;
	str_len = ft_strlen(str);
	while (len < str_len && is_separate_char(str[len]) == 0)
		len++;
	if (len == str_len)
		new->word_len = str_len;
	while (len < str_len && !ft_isspace(str[len]))
	{
		if (is_separate_char(str[len]) >= 3)
			break ;
		while (len < str_len && is_separate_char(str[len]) == 0)
			len++;
		c_status = is_separate_char(str[len++]);
		while (len < str_len && is_separate_char(str[len]) != c_status)
			len++;
		len++;
	}
	new->word_len = len;
	new->type = EXPANDABLE;
}

static void	get_redirect(char *str, t_token *new, t_flag *flag)
{
	if (!ft_strncmp(str, ">>", 2))
	{
		new->word_len = 2;
		new->type = REDIRECT;
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
	flag->redirect = FALSE;
}

static void	get_pipe(t_token *new, t_flag *flag)
{
	new->word_len = 1;
	new->type = PIPE;
	flag->pipe = FALSE;
}

void	get_token(t_token *new, t_flag *flag, char **str)
{
	if (flag->pipe == TRUE)
		get_pipe(new, flag);
	else if (flag->redirect == TRUE)
		get_redirect(*str, new, flag);
	else
		get_normal(*str, new);
}
