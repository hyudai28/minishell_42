#include "minishell.h"

static int	check_pipe_error(t_token *token)
{
	if (token->type == PIPE)
	{
		if (token->next->type == PIPE || token->next->type == TAIL)
		{
			return (1);
		}
	}
	return (0);
}

static int	check_redirect_error(t_token *token)
{
	if (token->type == REDIRECT || token->type == R_STDIN)
	{
		if (token->next->type == REDIRECT || token->next->type == PIPE || \
		token->next->type == TAIL || token->next->type == R_STDIN)
		{
			return (1);
		}
	}
	return (0);
}

int	parser(t_token *token, t_envlist *env)
{
	if (token->type == HEAD && token->next->type == PIPE)
	{
		error("Error \"syntax error around pipe\"", 1, env);
		return (1);
	}
	while (token->type != TAIL)
	{
		if (check_pipe_error(token) == 1)
		{
			error("Error \"syntax error around pipe\"", 1, env);
			return (1);
		}
		if (check_redirect_error(token) == 1)
		{
			error("Error \"syntax error around redirect\"", 1, env);
			return (1);
		}
		token = token->next;
	}
	return (0);
}
