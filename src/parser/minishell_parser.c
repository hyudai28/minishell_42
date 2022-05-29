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

static void	redirect_to_tail(t_token *prev, t_token *meta)
{
	t_token	*arg_last;
	t_token	*target;
	t_token	*tail;

	tail = meta->next;
	while (token_check_separate(tail->type) == 0)
		tail = tail->next;
	arg_last = tail->prev;
	target = meta->next;
	prev->next = target->next;
	target->next->prev = prev;
	arg_last->next = meta;
	meta->prev = arg_last;
	target->next = tail;
	tail->prev = target;
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
		else if (token->next->next->type != TAIL)
			redirect_to_tail(token->prev, token);
	}
	return (0);
}

static void	swap_head_meta(t_token *head, t_token *token)
{
	t_token	*meta;
	t_token	*target;
	t_token	*cmd;
	t_token	*tail;

	tail = token->next;
	while (token_check_separate(tail->type) == 0)
		tail = tail->next;
	meta = head->next;
	target = meta->next;
	cmd = target->next;
	tail->prev->next = meta;
	tail->prev = target;
	target->next = tail;
	target->prev = meta;
	meta->prev = cmd;
	cmd->prev = head;
	head->next = cmd;
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
	if (token->next->type != TAIL && (token->type == R_STDIN || token->type \
	== HEREDOC || token->type == REDIRECT || token->type == R_STDIN))
	{
		swap_head_meta(token->prev, token);
		return (0);
	}
	else if (token->type == R_STDIN || token->type == HEREDOC || \
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
		if (check_pipe(token, env) == 1)
			return (1);
		if (check_redirect(token, env) == 1)
			return (1);
		token = token->next;
	}
	return (0);
}
