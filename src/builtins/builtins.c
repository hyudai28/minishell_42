/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 21:24:14 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/06 18:12:07 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PATHNAME_SIZE 2048;
#define PWD 0;
#define ECHO 1;

int	char_count(char **count)
{
	int	ret;

	ret = 0;
	while (count[ret])
		ret++;
	return (ret);
}

int	builtins(char **cmds, t_envlist *env)
{
	int	argc;

	argc = char_count(cmds);
	if (!ft_strncmp(cmds[0], "echo", 5))
		return (builtin_echo(cmds, argc, env));
	else if (!ft_strncmp(cmds[0], "cd", 3))
		return (builtin_cd(cmds, argc, env));
	else if (!ft_strncmp(cmds[0], "pwd", 4))
		return (builtin_pwd(cmds, argc, env));
	else if (!ft_strncmp(cmds[0], "export", 7))
		return (builtin_export(cmds, argc, env));
	else if (!ft_strncmp(cmds[0], "unset", 5))
		return (builtin_unset(cmds, argc, env));
	else if (!ft_strncmp(cmds[0], "env", 4))
		return (builtin_env(cmds, argc, env));
	else if (!ft_strncmp(cmds[0], "exit", 5))
		return (builtin_exit(cmds, argc, env));
	else
		return (-1);
}
