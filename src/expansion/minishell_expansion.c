#include "minishell.h"

// クオーテーションをとる関数 word_lenの部分修正。

static size_t	count_quot(t_token *token)
{

}

static int	remove_quot(t_token *token)
{
	char	*tmp;

	token = token->next;
	while (token->type != TAIL)
	{
		if (token->word[0] == '\'' || token->word[0] == '\"')
		{
			tmp = token->word;
			token->word = malloc(token->word_len - 1);
			if (token->word == NULL)
				return (1);
			token->word[0] = '\0';
			ft_strlcpy(token->word, (tmp + 1), token->word_len - 1);
			token->word_len -= 2;
			free(tmp);
		}
		token = token->next;
	}
	return (0);
}

int	expansion(t_token *token, t_envlist *env)
{
	t_token	*head;

	head = token;
	token = token->next;
	while (token->type != TAIL)
	{
		expansion_dq(token, env);
		token = token->next;
	}
	if (remove_quot(head) != 0)
		return (1);
	return (0);
}
