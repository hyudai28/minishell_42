#include "minishell.h"

static int	outfd_setup(t_cmds *cmds, int *stdfd)
{
	int	stdout_fd;

	if (cmds->outfd_type == FD_STDOUT)
	{
		close(1);
		dup2(stdfd[1], 1);
	}
	else if (cmds->outfd_type == FD_REDIRECT)
	{
		close(1);
		stdout_fd = open(cmds->next->cmd[0], O_WRONLY | O_TRUNC | O_CREAT);
		dup2(stdout_fd, 1);
		if (stdout_fd != 1)
		{
			dprintf(2, "close = [%d]\n", stdout_fd);
			close(stdout_fd);
		}
	}
	return (0);
}

static int	infd_setup(t_cmds *cmds, int *stdfd)
{
	int	stdin_fd;

	if (cmds->infd_type == FD_R_STDIN)
	{
		close(0);
		stdin_fd = open(cmds->next->cmd[0], O_RDONLY);
		dup2(stdin_fd, 0);
		if (stdin_fd != 0)
			close(stdin_fd);
	}
	else
	{
		close(0);
		dup2(stdfd[0], 0);
	}
	return (0);
}

int	pipe_setup(t_cmds *cmds, int *infd, int stdfd[2], t_envlist *env)
{
	if (cmds->outfd_type == FD_PIPE_OUT || cmds->prev->outfd_type == FD_PIPE_OUT)
	{
		*infd = pipe_setfd(cmds, stdfd, *infd, env);
		if (*infd == -1)
			return (1);
	}
	else
	{
		infd_setup(cmds, stdfd);
		outfd_setup(cmds, stdfd);
		if (stdfd[0] == -1)
			return (1);
	}
	return (0);
}
