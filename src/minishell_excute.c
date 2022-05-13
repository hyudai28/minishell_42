#include "./include/minishell.h"

int	outfd_setup(t_cmds *cmds, int *stdfd);
int	infd_setup(t_cmds *cmds, int *stdfd);
void	inout_fd_setup(t_cmds *cmds, int *stdfd);

void	clean_fd(int *backup_fd, int pipe_fd)
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
//when error happen, ret_pipe_fd[0] == -1
	int	pipe_fd[2];


	if (cmds->outfd_type == C_PIPE)
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



void	fd_test()
{
	char buf[9];

	read(0, buf, 8);
	printf("buf = %s\n", buf);
}

int	pipe_setup(t_cmds *cmds, int *infd, int stdfd[2], t_envlist *env)
{
	if (cmds->outfd_type == C_PIPE || cmds->prev->outfd_type == C_PIPE)
	{
		*infd = pipe_setfd(cmds, stdfd, *infd, env);
		if (*infd == -1)
			return (1);
	}
	else
	{
		inout_fd_setup(cmds, stdfd);
		if (stdfd[0] == -1)
			return (1);
	}
	return (0);
}

int	minishell_excute(t_token *head, t_envlist *env)
{
	t_cmds	*cmds;
	int		pipe_infd;
	int		backup_stdfd[2];

	cmds = token_to_cmds(head);
	cmds = cmds->next;
	pipe_infd = -2;
	set_backup_fd(backup_stdfd);
	while (!cmds->head)
	{
		pipe_setup(cmds, &pipe_infd, backup_stdfd, env);
		builtins(cmds->cmd, env);
		cmds = cmds->next;
		if (cmds->head)
			break ;
		if (cmds->prev->outfd_type == C_REDIRECT || cmds->prev->outfd_type == IN_REDIRECT)
			cmds = cmds->next;
	}
	clean_fd(backup_stdfd, pipe_infd);
	cmds_destructor(cmds);
	return (doller_ret(0, env));
}









void	inout_fd_setup(t_cmds *cmds, int *stdfd)
{
	infd_setup(cmds, stdfd);
	outfd_setup(cmds, stdfd);
}





int	outfd_setup(t_cmds *cmds, int *stdfd)
{
	int		stdout_fd;

	if (cmds->outfd_type == C_STDOUT)
	{
		close(1);
		dup2(stdfd[1], 1);
	}
	else if (cmds->outfd_type == C_REDIRECT)
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








int	infd_setup(t_cmds *cmds, int *stdfd)
{
	int		stdin_fd;

	if (cmds->outfd_type == IN_REDIRECT)
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


void	do_parent()
{
	wait(NULL);
}

int	command_not_found_error(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg ,2);
	ft_putendl_fd(": command not found", 2);
	return (1);
}

void	pipex(char **cmds, t_envlist *env, char *path)
{
	pid_t	pid;
	char	**envp;

	pid = fork();
	if (pid < 0)
		error("fork error ", 1, env);
	if (pid == 0)
	{
		envp = envlist_to_char(env);
		if (execve(path, cmds, envp))
			error(strerror(errno), 1, env);
		envsplit_free(envp);
	}
	else
		do_parent();
}

char	*ft_pathjoin(char *bin_path, char *cmd, t_envlist *env)
{
	char	*add_slash;
	char	*ret_path;

	add_slash = ft_strjoin(bin_path, "/");
	if (!add_slash)
		error(strerror(errno), 1, env);
	ret_path = ft_strjoin(add_slash, cmd);
	free(add_slash);
	add_slash = NULL;
	if (!ret_path)
		error(strerror(errno), 1, env);
	return (ret_path);
}

//char	*slash_path(char *cmd)
//{
//	int	access_ret;

//	access_ret = access(cmd, X_OK);
//	if (access_ret == 0)
//		return (cmd);
//	return (NULL);
//}

char	*set_command(char *cmd, char **bin_path, t_envlist *env)
{
	int		path_i;
	int		access_ret;
	char *path;

	path_i = 0;
	access_ret = access(cmd, X_OK);
	if (access_ret == 0)
		return (ft_strdup(cmd));
	while (bin_path[path_i])
	{
		//if (cmd[0] == '/')
		//	return (slash_path(cmd));
		path = ft_pathjoin(bin_path[path_i], cmd, env);
		access_ret = access(path, X_OK);
		if (access_ret == 0)
			return (path);
		free(path);
		path = NULL;
		path_i++;
	}
	return (NULL);
}

char	*make_env_path(char **cmds, t_envlist *env)
{
	t_envlist	*path_node;
	char		**path_split;
	char		*ret_path;

	path_node = envlist_search("PATH", env);
	if (path_node == NULL)
		return (NULL);
	path_split = ft_split(path_node->value, ':');
	ret_path = set_command(cmds[0], path_split, env);
	envsplit_free(path_split);
	return (ret_path);
}

int	command_excute(char **cmds, t_envlist *env)
{
	char	*path;

	path = make_env_path(cmds, env);
	if (!path)
		command_not_found_error(cmds[0]);
	else
		pipex(cmds, env, path);
	free(path);
	path = NULL;
	return (0);
}
