#include "./include/minishell.h"
//# include <readline/readline.h>
//# include <readline/history.h>
//#include "/opt/homebrew/opt/readline/include/readline/readline.h"

sig_atomic_t signal_handled = 0;

int minishell(char *command, t_envlist *envp)
{
	t_token *head;
	int		ret_value;

	head = token_constructor();
	ret_value = lexer(command, head, envp);
	debug_all(head);
	if (!ret_value)
		ret_value = minishell_excute(head, envp);
	token_destructor(head);
	return (doller_ret(ret_value, envp));
}

int	check_state()
{
	if (signal_handled)
	{
		signal_handled = 0;
		//rl_delete_text(0, rl_end);
		//rl_done = 1;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char *command;
	t_envlist	*env_head;

	env_head = envlist_constructor(envp);
	//minishell_signal(command);
	//rl_event_hook = check_state;
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
