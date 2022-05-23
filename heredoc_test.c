# include<stdio.h>
# include<stdlib.h>
# include<string.h>
# include<ctype.h>
# include<stdbool.h>

# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

int main(int argc, char **argv)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];
	int		stdin_fd;


	pid = fork();
	if (pid < 0)
		perror("fork missed\n");
	if (pid == 0)
	{
		close(0);
		stdin_fd = open("./my_list", O_RDONLY);
		dup2(stdin_fd, 0);
		if (execve("/bin/cat", NULL, NULL))
		{
			perror("execve error\n");
			exit (1);
		}
	}
	else
		wait(&status);
}