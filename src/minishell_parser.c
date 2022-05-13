#include "./include/minishell.h"


int parser(t_token *token, t_flag *flag, t_envlist *env)
{
	if (token->type == HEAD && token->next->type == PIPE)
	{
		error("Error \"syntax error around pipe\"", 1, env);
		return (1);
	}
	while (token->type != TAIL)
	{
		if (token->type == PIPE)
			if (token->next->type == PIPE || token->next->type == TAIL)
			{
				error("Error \"syntax error around pipe\"", 1, env);
				return (1);
			}
		if (token->type == REDIRECT || token->type == R_STDIN)
			if (token->next->type == REDIRECT || token->next->type == PIPE || token->next->type == TAIL || token->next->type == R_STDIN)
			{
				error("Error \"syntax error around redirect\"", 1, env);
				return (1);
			}
		token = token->next;
	}
	return (0);
}
