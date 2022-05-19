#include "minishell.h"

sig_atomic_t	g_signal_handled = 0;

int	minishell(char *command, t_envlist *envp)
{
	t_token	*head;
	int		result;

	head = token_constructor();
	if (lexer(command, head) != 0)
		return (1);
	debug_all(head);
	if (heredocument(head))
		return (1);
	if (parser(head, envp) != 0)
		return (1);
	if (expansion(head, envp) != 0)
		return (1);
	//debug_all(head);
	result = minishell_excute(head, envp);
	token_destructor(head);
	return (doller_ret(result, envp));
}

int	check_state(void)
{
	if (g_signal_handled)
	{
		g_signal_handled = 0;
		//rl_delete_text(0, rl_end);
		//rl_done = 1;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*command;
	t_envlist	*env_head;

	(void)argv;
	(void)argc;
	command = NULL;
	env_head = envlist_constructor(envp);
	minishell_signal();
	rl_event_hook = check_state;
	while (1)
	{
		command = readline("minishell > ");
		if (command == NULL)
			return (!write(2, "exit", 4));
		else if (ft_strlen(command) > 0)
		{
			add_history(command);
			minishell(command, env_head);
		}
		free(command);
		//system("leaks minishell");
	}
	return (env_head->doller_ret);
}
