/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:51:50 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 23:51:50 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe(t_token *token, t_envlist *env)
{
	if (token->type == PIPE)
	{
		if (token->next->type == TAIL)
		{
			error("Error \"syntax error around pipe\"", 1, env);
			return (1);
		}
		else if (token->next->type == PIPE)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(token->next->word, 2);
			error("'", 2, env);
			return (1);
		}
	}
	return (0);
}

static int	check_redirect(t_token *token, t_envlist *env)
{
	if (token->type == REDIRECT || token->type == APPEND_REDIRECT || \
			token->type == R_STDIN || token->type == HEREDOC)
	{
		if (token->next->type == TAIL)
		{
			error(\
			"bash: syntax error near unexpected token `newline'", 2, env);
			return (1);
		}
		else if (token->next->type == REDIRECT || \
		token->next->type == APPEND_REDIRECT || \
		token->next->type == R_STDIN || token->next->type == HEREDOC)
		{
			ft_putstr_fd(\
			"minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(token->next->word, 2);
			error("'", 2, env);
			return (1);
		}
	}
	return (0);
}

static int	check_head_type(t_token *token, t_envlist *env)
{
	if (token->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->word, 2);
		error("'", 2, env);
		return (1);
	}
	if (token->next->type == TAIL)
	{
		if (token->type == R_STDIN || token->type == HEREDOC || \
		token->type == REDIRECT)
		{
			error(\
			"minishell: syntax error near unexpected token `newline'", 2, env);
			return (1);
		}
		else if (token->type == R_STDIN)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(token->next->word, 2);
			error(": No such file or directory", 2, env);
		}
	}
	return (0);
}

static int	check_quot(const char *line)
{
	char	*quot;

	while (*line != '\0')
	{
		while (*line != '\0' && *line != '\'' && *line != '\"')
			line++;
		if (*line == '\0')
			return (0);
		quot = ft_strchr(line + 1, *line);
		if (quot == NULL)
		{
			printf("minishell: quotation no matching.\n");
			return (1);
		}
		line = quot;
		line++;
	}
	return (0);
}

int	parser(t_token *token, t_envlist *env)
{
	t_token	*head;

	head = token;
	token = token->next;
	if (check_head_type(token, env) == 1)
	{
		token_destructor(token);
		return (1);
	}
	while (token->type != TAIL)
	{
		if (check_quot(token->word) == 1 || \
			check_pipe(token, env) == 1 || check_redirect(token, env) == 1)
		{
			token_destructor(head);
			return (1);
		}
		token = token->next;
	}
	return (0);
}
