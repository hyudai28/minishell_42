/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:58:41 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/16 15:51:21 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	//still reachable 218 blocks

int	event_hook(void)
{
	if (g_signal_handled)
	{
		g_signal_handled = 1;
	}
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
}

static void	command_is_null(t_envlist *env)
{
	envlist_destructor(env);
	write(2, "exit", 4);
	exit(0);
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
	}
	envlist_destructor(env_head);
	return (env_head->doller_ret);
}
