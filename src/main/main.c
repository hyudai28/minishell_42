#include "minishell.h"

int	minishell(char *command, t_envlist *envp)
{
	t_token	*head;
	int		result;

	head = token_constructor();
	if (lexer(command, head) == 1)
		return (free_structors(head, NULL, NULL));
	// if (heredocument(head))
		// return (1);
	if (parser(head, envp) != 0)
		return (1);
	if (expansion(head, envp) != 0)
		return (1);
	// debug_all(head);
	result = minishell_execute(head, envp);
	token_destructor(head);
	return (doller_ret(result, envp));
}

int	event_hook(void)
{
	if (g_signal_handled)
	{
		g_signal_handled = 1;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*command;
	t_envlist	*env_head;

	(void)argv;
	(void)argc;
	g_signal_handled = 0;
	command = NULL;
	env_head = envlist_constructor(envp);
	minishell_signal();
	rl_signal_event_hook = event_hook;
	while (1)
	{
		command = readline("minishell > ");
		if (g_signal_handled != 0)
			env_head->doller_ret = g_signal_handled;
		g_signal_handled = 0;
		if (command == NULL)
			return (!write(2, "exit", 4));
		else if (ft_strlen(command) > 0)
		{
			add_history(command);
			minishell(command, env_head);
		}
		//free(command);
		//system("leaks minishell");
	}
	return (env_head->doller_ret);
}
