/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:35:35 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 18:35:35 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_parent(void)
{
	int	status;

	wait(&status);
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

int	pipex(char **cmds, t_envlist *env, char *path)
{
	pid_t	pid;
	char	**envp;

	pid = fork();
	if (pid < 0)
		error("fork error ", 1, env);
	if (pid == 0)
	{
		execute_signal();
		envp = envlist_to_key(env);
		if (execve(path, cmds, envp))
		{
			error(strerror(errno), 1, env);
			exit (1);
		}
		split_free(envp);
		exit (0);
	}
	else if (0 < pid)
		return (do_parent());
	return (1);
}
