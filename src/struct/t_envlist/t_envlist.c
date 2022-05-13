#include "t_token.h"

t_envlist	*envlist_constructor(char **envp)
{
	t_envlist	*new;
	t_envlist	*head;
	int			env_i;

	new = (t_envlist *)malloc(sizeof(t_envlist));
	ft_memset(new, 0, sizeof(t_envlist));
	new->prev = NULL;
	new->next = NULL;
	new->head = 1;
	new->doller_ret = 0;
	new->key = NULL;
	new->value = NULL;
	env_i = -1;
	head = new;
	while (envp[++env_i])
	{
		envlist_add(envp[env_i], new, head);
		new = new->next;
	}
	return (head);
}

void	envlist_destructor(t_envlist *envlist)
{
	int		i;
	t_envlist	*tmp;

	envlist = envlist->next;
	while (envlist->head != 1)
	{
		i = 0;
		free(envlist->key);
		envlist->key = NULL;
		free(envlist->value);
		envlist->value = NULL;
		tmp = envlist;
		envlist = envlist->next;
		free(tmp);
		tmp = NULL;
	}
	free(envlist);
	envlist = NULL;
}

void	envlist_add(char *new_line, t_envlist *prev, t_envlist *head)
{
	t_envlist *new;

	new = (t_envlist *)malloc(sizeof(t_envlist));
	ft_memset(new, 0, sizeof(t_envlist));
	new->prev = prev;
	new->next = head;
	new->head = 0;
	new->doller_ret = 0;
	envlist_set_keyvalue(new, new_line);
	prev->next = new;
	head->prev = new;
}

void	envlist_set_keyvalue(t_envlist *target, char *new_line)
{
	int chr;

	chr = ft_strchr_gnl(new_line, '=');
	if (chr == -1)
	{
		target->key = ft_strdup(new_line);
		target->value = NULL;
		return ;
	}
	target->key = ft_substr(new_line, 0, chr);
	target->value = ft_substr(new_line, chr + 1, ft_strlen(new_line) - chr);
}

t_envlist	*envlist_search(char *tr_line, t_envlist *node)
{
	size_t	tr_len;

	if (node->head)
		node = node->next;
	tr_len = ft_strlen(tr_line);
	while (!node->head)
	{
		if (!ft_strncmp(tr_line, node->key, tr_len + 1))
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	envlist_delete(char *delete_line, t_envlist *head)
{
	t_envlist *target;
	t_envlist *target_prev;
	t_envlist *target_next;

	target = envlist_search(delete_line, head);
	if (!target)
		return ;
	target_next = target->next;
	target_prev = target->prev;
	target_prev->next = target_next;
	target_next->prev = target_prev;
	free(target->key);
	target->key = NULL;
	free(target->value);
	target->value = NULL;
	free(target);
	target = NULL;
}

int	envlist_node_count(t_envlist *head)
{
	t_envlist	*tmp;
	int			node_count;

	if (!head)
		return (0);
	tmp = head->next;
	node_count = 0;
	while (!tmp->head)
	{
		tmp = tmp->next;
		node_count++;
	}
	return (node_count);
}

char	**envlist_to_char(t_envlist *head)
{
	t_envlist	*tmp;
	char	*key;
	char	**split;

	tmp = head->next;
	key = NULL;
	while (!tmp->head)
	{
		key = token_strjoin(key, tmp->key);
		key = token_strjoin(key, " ");
		tmp = tmp->next;
	}
	split = ft_split(key, ' ');
	free(key);
	key = NULL;
	return (split);
}

void	envlist_show(t_envlist *env)
{
	int i;

	i = 0;
	if (env->head)
		env = env->next;
	while (!env->head)
	{
		printf("i=[%d] key=[%s], value=[%s]\n", i++, env->key, env->value);
		env = env->next;
	}
}
