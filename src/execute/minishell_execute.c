/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:34:15 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/12 00:09:12 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_directory(char *msg)
{
	size_t	i;

	i = 0;
	while (msg[i] != '\0')
	{
		if (msg[i] == '/')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	command_not_found_error(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	if (check_directory(msg) == 1)
		ft_putendl_fd(": No such file or directory", 2);
	else
		ft_putendl_fd(": command not found", 2);
	return (1);
}

int	command_execute(char **cmds, t_envlist *env)
{
	char	*path;
	int		result;

	path = get_command_path(cmds, env);
	if (!path)
	{
		command_not_found_error(cmds[0]);
		return (127);
	}
	else
		result = pipex(cmds, env, path);
	free(path);
	path = NULL;
	return (result);
}

int	minishell_execute(t_cmds *cmds, t_envlist *env)
{
	int		pipe_infd;
	int		backup_default_stdfd[2];
	int		backup_stdfd[2];
	int		result;

	backup_default_stdfd[0] = dup(0);
	backup_default_stdfd[1] = dup(1);
	backup_stdfd[0] = dup(0);
	backup_stdfd[1] = dup(1);
	if (!cmds)
		error("open err", 1, env);
	if (!cmds->next->cmd)
		return (0);
	pipe_infd = -2;
	cmds = cmds->next;
	while (!cmds->head)
	{
		pipe_setup(cmds, &pipe_infd, backup_stdfd, env);
		result = builtins(cmds->cmd, env);
		if (result == -1)
			result = command_execute(cmds->cmd, env);
		cmds = cmds->next;
	}
	cmds_destructor(cmds);
	clean_fd(backup_default_stdfd[0], 0);
	clean_fd(backup_default_stdfd[1], 1);
	return (result);
}
