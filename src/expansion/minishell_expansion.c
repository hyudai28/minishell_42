#include "minishell.h"

int expansion(t_token *token, t_flag *flag, t_envlist *env)
{
	token = token->next;
	while (token->type != TAIL)
	{
		if (token->type == NONEXPANDABLE_SQ)
		{
			;
		}
		else if (token->type == EXPANDABLE_DQ)
		{
			expansion_dq(token, env);
		}
		else
		{
			expansion_dq(token, env);
		}
		token = token->next;
	}
	return (0);
}

int	closed_quot(const char *line)
{
	int	squot_count;
	int	dquot_count;
	int	line_i;

	squot_count = 0;
	dquot_count = 0;
	line_i = 0;
	while (line[line_i])
	{
		if (line[line_i] == '\'')
			squot_count++;
		else if (line[line_i] == '"')
			dquot_count++;
		line_i++;
	}
	if (squot_count != 0 && squot_count % 2 == 1)
		return (1);
	if (dquot_count != 0 && dquot_count % 2 == 1)
		return (1);
	return (0);
}

// クオーテーションをとる関数 word_lenの部分修正。
int remove_quot(t_token *token, t_flag *flag, t_envlist *env)
{
	char	*tmp;

	while (token->type != TAIL)
	{
		if (token->type == NONEXPANDABLE_SQ || token->type == EXPANDABLE_DQ)
		{
			tmp = token->word;
			// if (token->word_len != 2)
			// 	token->word = malloc()
			// if (token->word_len == 2)
			// {
			// 	token->word = malloc(1);
			// 	if (token->word == NULL)
			// 		return (1);
			// 	token->word[0] = '\0';
			// }
			// else
			// {
			token->word = malloc(token->word_len - 1);
			if (token->word == NULL)
				return (1);
			token->word[0] = '\0';
			ft_strlcpy(token->word, (tmp + 1), token->word_len - 1);
			// }
			token->word_len -= 2;
			free(tmp);
		}
		token = token->next;
	}
	return (0);
}
