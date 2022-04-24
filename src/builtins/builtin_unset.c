
#include "../include/minishell.h"

int	builtin_unset(t_envlist *head, char **cmds)
{
	char	*delete;

	if (cmds[1])
	{
		delete = cmds[1];
		if (!head->next->head)
			return (0);
		envlist_delete(delete, head);
	}
	return (0);
}