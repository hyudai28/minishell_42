#include "minishell.h"

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

void	clean_fd(int backup_fd, int close_fd)
{
	close(close_fd);
	dup2(backup_fd, close_fd);
	close(backup_fd);
}

int	pipe_setup(t_cmds *cmds, int *infd, int stdfd[2], t_envlist *env)
{
	int	pipe_fd[2];
	int	redirect_fd;

	if (cmds->infd_type == FD_PIPE_IN)
	{
		clean_fd(*infd, 0);
	}
	else if (cmds->infd_type == FD_R_STDIN)
	{
		;
	}
	if (cmds->outfd_type == FD_STDOUT)
	{
		clean_fd(stdfd[1], 1);
		stdfd[1] = dup(1);
		outfd_setup(cmds, stdfd);
	}
	else if (cmds->outfd_type == FD_PIPE_OUT)
	{
		if (pipe(pipe_fd) != 0)
		{
			error(strerror(errno), 1, env);
			return (-1);
		}
		clean_fd(pipe_fd[1], 1);
		*infd = pipe_fd[0];
		return (0);
	}
	else if (cmds->outfd_type == FD_REDIRECT)
	{
		redirect_fd = open(cmds->next->cmd[0], O_WRONLY | O_TRUNC | O_CREAT);
		clean_fd(redirect_fd, 1);
	}
	else if (cmds->outfd_type == FD_APPEND_REDIRECT)
	{
		redirect_fd = open(cmds->next->cmd[0], O_WRONLY | O_APPEND | O_CREAT);
		clean_fd(redirect_fd, 1);
	}
	// if (stdfd[0] == -1)
	// 	return (1);
	return (0);
}
