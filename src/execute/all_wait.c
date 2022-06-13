/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:13:02 by hyudai            #+#    #+#             */
/*   Updated: 2022/06/13 23:04:51 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	is_builtins(char **cmds)
{
	if (!cmds)
		return (0);
	if (!ft_strncmp(cmds[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(cmds[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(cmds[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmds[0], "export", 7))
		return (1);
	else if (!ft_strncmp(cmds[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(cmds[0], "env", 4))
		return (1);
	else if (!ft_strncmp(cmds[0], "exit", 5))
		return (1);
	return (0);
}

int	fork_wait(t_cmds *cmds, t_envlist *env)
{
	int	status;
	if (cmds->pid == -1)
		return (0);
	waitpid(cmds->pid, &status, 0);
	if (status == -1)
		return (1);
	if (WIFEXITED(status) == 1)
	{
		return (WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status) == 1)
	{
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	all_wait(t_cmds *cmds, t_envlist *env, int result)
{
	int	ret;

	ret = 0;
	while (cmds->head != 1)
	{
		if (is_builtins(cmds->cmd))
		{
			printf("abc\n");
			ret = result;
		}
		else
		{
			printf("def\n");
			ret = fork_wait(cmds, env);
		}
		cmds = cmds->next;
	}
	return (ret);
}