#include "minishell.h"

void	clean_fd(int *backup_fd)
{
	close(0);
	dup2(backup_fd[0], 0);
	close(backup_fd[0]);
	close(1);
	dup2(backup_fd[1], 1);
	close(backup_fd[1]);
}

void	set_backup_fd(int *stdfd)
{
	stdfd[0] = dup(0);
	stdfd[1] = dup(1);
}

int	pipe_setfd(t_cmds *cmds, int *stdfd, int infd, t_envlist *env)
{
	int	pipe_fd[2];
	//when error happen, ret_pipe_fd[0] == -1
	if (cmds->outfd_type == FD_PIPE_OUT)
	{
		if (pipe(pipe_fd) != 0)
		{
			error(strerror(errno), 1, env);
			return (-1);
		}
		close (1);
		dup2(pipe_fd[1], 1);
		if (pipe_fd[1] != 1)
			close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	else if (infd != -2)
	{
		close(0);
		dup2(infd, 0);
		if (infd != 0)
			close(infd);
		close(1);
		dup2(stdfd[1], 1);
		close (stdfd[1]);
		stdfd[1] = dup(1);
		return (-2);
	}
	else
		return (0);
	return (0);
}
