
#include "minishell.h"



int	builtin_env(char **cmds, int argc, t_envlist *envp)
{
	(void)argc;
	if (envp->next->head)
		return (0);
	envp = envp->next;
	while(envp->head != 1)
	{
		if (envp->value)
		{
			ft_putstr_fd(envp->key, 1);
			write(1, "=", 1);
			ft_putendl_fd(envp->value, 1);
		}
		envp = envp->next;
	}
	return (0);
}
