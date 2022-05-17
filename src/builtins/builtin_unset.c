#include "minishell.h"

int	builtin_unset(char **cmds, int argc, t_envlist *head)
{
	char	*delete;

	(void)argc;
	if (cmds[1])
	{
		delete = cmds[1];
		if (!head->next->head)
			return (0);
		envlist_delete(delete, head);
	}
	return (0);
}
