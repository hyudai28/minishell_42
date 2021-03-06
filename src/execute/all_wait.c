/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 23:13:02 by hyudai            #+#    #+#             */
/*   Updated: 2022/06/20 22:19:00 by mfujishi         ###   ########.fr       */
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

int	fork_wait(t_cmds *cmds)
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

int	command_not_found(t_cmds *cmds, t_envlist *env)
{
	char	*path;

	path = get_command_path(cmds->cmd, env);
	if (!path)
	{
		return (127);
	}
	free(path);
	path = NULL;
	return (0);
}

int	all_wait(t_cmds *cmds, int result, int *stdfd, t_envlist *env)
{
	int	ret;

	ret = 0;
	if (cmds->head == 1)
		cmds = cmds->next;
	while (cmds->head != 1)
	{
		if (is_builtins(cmds->cmd))
			ret = result;
		else if (command_not_found(cmds, env))
			ret = result;
		else
			ret = fork_wait(cmds);
		cmds = cmds->next;
	}
	clean_fd(stdfd[0], 0);
	clean_fd(stdfd[1], 1);
	return (ret);
}
