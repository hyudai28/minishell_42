/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:58:41 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/21 23:30:46 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	//still reachable 218 blocks

int	event_hook(void)
{
	if (g_signal_handled)
	{
		g_signal_handled = 1;
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return (0);
}

static int	all_space(char *command)
{
	size_t	i;

	i = 0;
	while (ft_isspace(command[i]))
		i++;
	if (command[i] == '\0')
		return (1);
	return (0);
}

static void	main_constructor(int argc, char **argv, char **command)
{
	(void)argv;
	(void)argc;
	*command = NULL;
	g_signal_handled = 0;
	minishell_signal();
	rl_signal_event_hook = event_hook;
	rl_event_hook = NULL;
}

static void	command_is_null(t_envlist *env)
{
	int	exit_status;

	exit_status = env->doller_ret;
	envlist_destructor(env);
	write(2, "exit", 4);
	exit(exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char		*command;
	t_envlist	*env_head;

	main_constructor(argc, argv, &command);
	env_head = envlist_constructor(envp);
	while (1)
	{
		command = readline("minishell > ");
		if (command == NULL)
			command_is_null(env_head);
		if (g_signal_handled != 0)
			env_head->doller_ret = g_signal_handled;
		g_signal_handled = 0;
		if (ft_strlen(command) > 0 && all_space(command) == 0)
		{
			add_history(command);
			minishell(command, env_head);
		}
		else
			free(command);
		if (g_signal_handled)
			ft_putchar_fd('\n', 2);
	}
	envlist_destructor(env_head);
	return (env_head->doller_ret);
}
