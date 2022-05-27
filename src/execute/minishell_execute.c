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

int	minishell_execute(t_token *head, t_envlist *env)
{
	t_cmds	*cmds;
	int		pipe_infd;
	int		backup_stdfd[2];
	int		result;

	cmds = token_to_cmds(head);
	debug_cmds(cmds->next);
	pipe_infd = -2;
	set_backup_fd(backup_stdfd);
	cmds = cmds->next;
	while (!cmds->head)
	{
		pipe_setup(cmds, &pipe_infd, backup_stdfd, env);
		result = builtins(cmds->cmd, env);
		if (result == -1)
			result = command_execute(cmds->cmd, env);
		if (cmds->outfd_type == C_REDIRECT || cmds->outfd_type == IN_REDIRECT)
			cmds = cmds->next;
		cmds = cmds->next;
	}
	clean_fd(backup_stdfd);
	cmds_destructor(cmds);
	return (result);
}
