#include "minishell.h"	//still reachable 218 blocks

int	minishell(char *command, t_envlist *envp)
{
	t_token	*head;
	t_cmds	*cmds;
	int		result;

	head = token_constructor();
	if (lexer(command, head, envp) == 1)
		return (1);
	if (parser(head, envp) == 1)
		return (1);
	if (heredocument(head, envp) == 1)
		return (1);
	if (expansion(head, envp) == 1)
		return (1);
	cmds = token_to_cmds(head);
	token_destructor(head);
	result = minishell_execute(cmds, envp);
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
	int			exit_status;


	(void)argv;
	(void)argc;
	g_signal_handled = 0;
	command = NULL;
	env_head = envlist_constructor(envp);
	if (env_head == NULL)
	{
		envlist_destructor(env_head);
		return (1); //malloc error
	}
	minishell_signal();
	rl_signal_event_hook = event_hook;
	while (1)
	{
		command = readline("minishell > ");
		if (command == NULL)
		{
			envlist_destructor(env_head);
			return (!write(2, "exit", 4));
		}
		if (g_signal_handled != 0)
			env_head->doller_ret = g_signal_handled;
		g_signal_handled = 0;
		if (ft_strlen(command) > 0)
		{
			add_history(command);
			minishell(command, env_head);
		}
		//free(command);
		system("leaks minishell");
	}
	exit_status = env_head->doller_ret;
	envlist_destructor(env_head);
	return (env_head->doller_ret);
}
