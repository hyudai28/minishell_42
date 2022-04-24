#include "./include/minishell.h"


int parcer(t_token *token, t_flag *flag, t_envlist *env)
{
	if (token->type == HEAD && token->next->type == PIPE)
		return (error("Error \"syntax error around pipe\"", 1, env));
	while (token->type != TAIL)
	{
		if (token->type == PIPE)
			if (token->next->type == PIPE || token->next->type == TAIL)
				return (error("Error \"syntax error around pipe\"", 1, env));
		if (token->type == REDIRECT || token->type == R_STDIN)
			if (token->next->type == REDIRECT || token->next->type == PIPE || token->next->type == TAIL || token->next->type == R_STDIN)
				return (error("Error \"syntax error around redirect\"", 1, env));
		token = token->next;
	}
	return (TRUE);
}