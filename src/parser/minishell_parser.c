#include "minishell.h"

static int	check_pipe_error(t_token *token, t_envlist *env)
{
	if (token->type == PIPE)
	{
		if (token->next->type == PIPE)
		{
			if (token->next->word[0] == '|' && token->next->word[1] == '\0')
				error(\
				"minishell: syntax error near unexpected token `|'", 2, env);
			else if (token->next->word[0] == '|' && token->next->word[1] == '|')
				error(\
				"minishell: syntax error near unexpected token `||'", 2, env);
			return (1);
		}
		if (token->next->type == TAIL)
		{
			error("Error \"syntax error around pipe\"", 1, env);
			return (1);
		}
	}
	return (0);
}

static int	check_redirect_error(t_token *token, t_envlist *env)
{
	if (token->type == REDIRECT || token->type == R_STDIN)
	{
		if (token->next->type == REDIRECT || token->next->type == PIPE ||
		token->next->type == TAIL || token->next->type == R_STDIN)
		{
			error("Error \"syntax error around redirect\"", 1, env);
			return (1);
		}
	}
	return (0);
}

static int	check_head_type(t_token *token, t_envlist *env)
{
	if (token->type == PIPE)
	{
		if (token->word[0] == '|' && token->word[1] == '\0')
			error("minishell: syntax error near unexpected token `|'", 2, env);
		else if (token->word[0] == '|' && token->word[1] == '|')
			error("minishell: syntax error near unexpected token `||'", 2, env);
		return (1);
	}
	else if ((token->type == R_STDIN || token->type == HEREDOC || \
	token->type == REDIRECT) && token->next->type == TAIL)
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
	return (0);
}

static int	check_quot(const char *line, enum e_token_type type)
{
	char	*quot;

	while (*line != '\0')
	{
		while (*line != '\0' && *line != '\'' && *line != '\"')
			line++;
		if (*line == '\0')
			return (type);
		quot = ft_strchr(line + 1, *line);
		if (quot == NULL)	//片方しかない
			exit(1);
		line = quot;
		line++;
	}
	return (type);
}

int	parser(t_token *token, t_envlist *env)
{
	if (check_head_type(token->next, env) == 1)
		return (1);
	token = token->next;
	while (token->type != TAIL)
	{
		token->type = check_quot(token->word, token->type);
		if (check_pipe_error(token, env) == 1)
			return (1);
		if (check_redirect_error(token, env) == 1)
			return (1);
		token = token->next;
	}
	return (0);
}
