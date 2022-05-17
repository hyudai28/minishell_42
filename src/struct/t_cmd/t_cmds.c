#include "t_token.h"

t_cmds	*cmds_constructor(int head, t_cmds *cmd_head)
{
	t_cmds	*new;

	new = (t_cmds *)malloc(sizeof(t_cmds));
	//malloc失敗処理
	ft_memset(new, 0, sizeof(t_cmds));
	new->prev = NULL;
	if (head)
	{
		new->next = NULL;
		new->head = 1;
	}
	else
	{
		new->next = cmd_head;
		new->head = 0;
	}
	new->outfd_type = C_STDOUT;
	new->cmd = NULL;
	return (new);
}

void	cmds_destructor(t_cmds *cmds)
{
	int		i;
	t_cmds	*tmp;

	cmds = cmds->next;
	while (cmds->head != 1)
	{
		i = 0;
		while (cmds->cmd[i])
		{
			free(cmds->cmd[i]);
			cmds->cmd[i] = NULL;
			i++;
		}
		free(cmds->cmd);
		cmds->cmd = NULL;
		tmp = cmds;
		cmds = cmds->next;
		free(tmp);
		tmp = NULL;
	}
	free(cmds);
	cmds = NULL;
}

bool	token_finish(t_token_type type)
{
	if (type == TAIL)
		return (2);
	if (type == PIPE || type == REDIRECT || type == R_STDIN)
		return (1);
	return (0);
}

char	*token_strjoin(char *cmd_line, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	if (cmd_line == NULL)
		len1 = 0;
	else
		len1 = ft_strlen(cmd_line);
	if (s2 == NULL)
		len2 = 0;
	else
		len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, cmd_line, len1);
	ft_memcpy((str + len1), s2, len2);
	str[len1 + len2] = '\0';
	free(cmd_line);
	cmd_line = NULL;
	return (str);
}

t_token	*cmds_set_fd(t_cmds *new, t_token *token)
{
	if (token->type == PIPE)
	{
		new->outfd_type = 2;
		new->outfd_line = NULL;
		return (token->next);
	}
	if (token->type == REDIRECT)
	{
		new->outfd_type = 1;
		token = token->next;
		if (token->word)
			new->outfd_line = ft_strdup(token->word);
		else
		{
			ft_putendl_fd("redirect error", 2);
			return (NULL);
		}
	}
	return (token);
}

t_cmds_out_fd	cmds_setoutfd(t_token_type type)
{
	if (type == PIPE)
		return (C_PIPE);
	if (type == REDIRECT)
		return (C_REDIRECT);
	return (C_STDOUT);
}

t_cmds_out_fd	cmds_setinfd(t_token_type type)
{
	if (type == PIPE)
		return (IN_PIPE);
	if (type == R_STDIN)
		return (IN_REDIRECT);
	return (C_STDOUT);
}

size_t	count_token(t_token *token)
{
	size_t	size;

	size = 0;
	while (!token_finish(token->type))
	{
		size++;
		token = token->next;
	}
	return (size);
}

char	**separate_token(t_token *token)
{
	char	**cmd;
	size_t	size;
	size_t	index;

	size = count_token(token);
	cmd = (char **)malloc(sizeof(char *) * (size + 1));
	if (cmd == NULL)
		return (NULL);
	index = 0;
	while (!token_finish(token->type))
	{
		cmd[index] = ft_strdup(token->word);
		//malloc失敗時にfree処理
		token = token->next;
		index++;
	}
	cmd[index] = NULL;
	return (cmd);
}

t_cmds	*token_to_cmds(t_token *token)
{
	t_cmds	*head;
	t_cmds	*new;
	t_cmds	*now;

	head = cmds_constructor(TRUE, NULL);
	now = head;
	token = token->next;
	while (token->type != TAIL)
	{
		new = cmds_constructor(FALSE, head);
		new->cmd = separate_token(token);
		while (!token_finish(token->type))
			token = token->next;
		if (token->type == PIPE || token->type == REDIRECT)
		{
			new->outfd_type = cmds_setoutfd(token->type);
			token = token->next;
		}
		else if (token->prev->type == PIPE || token->type == R_STDIN)
		{
			if (token->type == R_STDIN)
				new->outfd_type = cmds_setinfd(token->type);
			else
				new->outfd_type = cmds_setinfd(token->prev->type);
			token = token->next;
		}
		new->prev = now;
		now->next = new;
		head->prev = now;
		now = now->next;
	}
	return (head);
}
