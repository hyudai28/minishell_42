#include "t_token.h"

void	ft_strlen_others(char *str, t_token *new);
void	ft_strlen_redirect(char *str, t_token *new, t_flag *flag);
void	ft_strlen_pipe(t_token *new, t_flag *flag);

t_token	*token_constructor(void)
{
	t_token	*head;

	head = (t_token *)malloc(sizeof(t_token));//失敗
	ft_memset(head, 0, sizeof(t_token));
	head->next = NULL;
	head->prev = NULL;
	head->type = HEAD;
	head->word = NULL;
	head->head = 1;
	return (head);
}

void	token_destructor(t_token *token)
{
	t_token	*tmp;

	while (token->type != TAIL)
	{
		if (token->word)
		{
			free(token->word);
			token->word = NULL;
		}
		tmp = token;
		token = token->next;
		free(tmp);
		tmp = NULL;
	}
	free(token);
	token = NULL;
}

void	get_token_len(t_token *new, t_flag *flag, char **str)
{
	if (flag->pipe == TRUE)
		ft_strlen_pipe(new, flag);
	else if (flag->redirect == TRUE)
		ft_strlen_redirect(*str, new, flag);
	else
		ft_strlen_others(*str, new);
}

t_token	*new_token(t_flag *flag, t_token *cur, char **str)
{
	t_token	*new;

	if (**str == '\0')
		return (cur);
	new = (t_token *)malloc(sizeof(t_token));//失敗
	ft_memset(new, 0, sizeof(t_token));
	cur->next = new;
	new->prev = cur;
	get_token_len(new, flag, str);
	new->word = (char *)malloc(new->word_len + 1);//失敗
	ft_strlcpy(new->word, *str, new->word_len + 1);
	if (new->word_len == WORD_LEN_ERROR)
		return (new);
	(*str) += (new->word_len);
	new->head = 0;
	return (new);
}

t_token	*end_token(t_token *cur)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	ft_memset(new, 0, sizeof(t_token));
	new->type = TAIL;
	cur->next = new;
	new->prev = cur;
	return (new);
}

void	flag_set(t_flag *flag, char c)
{
	if (c == '>' || c == '<')
		flag->redirect = TRUE;
	else if (c == '|')
		flag->pipe = TRUE;
}
