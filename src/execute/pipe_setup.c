#include "minishell.h"

void	clean_fd(int backup_fd, int close_fd)
{
	close(close_fd);
	dup2(backup_fd, close_fd);
	close(backup_fd);
}

int	pipe_setup(t_cmds *cmds, int *infd, int stdfd[2], t_envlist *env)
{
	int	pipe_fd[2];
	int	out_redirect_fd;
	int	in_redirect_fd;
	char	*heredoc1 = "a\n";
	char	*heredoc2 = "b\n";
	char	*heredoc3 = "c\n";

	if (cmds->infd_type == FD_PIPE_IN)
	{
		clean_fd(*infd, 0);
	}
	else if (cmds->infd_type == FD_R_STDIN)
	{
		in_redirect_fd = open(cmds->next->cmd[0], O_RDONLY);
		clean_fd(in_redirect_fd, 0);
	}
	else if (cmds->infd_type == FD_HEREDOC)
	{
		if (pipe(pipe_fd) != 0)
		{
			error(strerror(errno), 1, env);
			return (-1);
		}
		ft_putendl_fd(cmds->next->cmd[0], pipe_fd[1]);
		clean_fd(pipe_fd[0], 0);
		clean_fd(pipe_fd[1], 1);
	}
	if (cmds->outfd_type == FD_STDOUT)
	{
		clean_fd(stdfd[1], 1);
		stdfd[1] = dup(1);
		close(1);
		dup2(stdfd[1], 1);
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
		out_redirect_fd = open(cmds->next->cmd[0], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		clean_fd(out_redirect_fd, 1);
	}
	else if (cmds->outfd_type == FD_APPEND_REDIRECT)
	{
		out_redirect_fd = open(cmds->next->cmd[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
		clean_fd(out_redirect_fd, 1);
	}
	return (0);
}
