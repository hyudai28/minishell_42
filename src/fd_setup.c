#include "./include/minishell.h"
#include "./include/t_token.h"

#define STDOUT 1
#define PIPE 2
#define REDIRECT 3

void	fd_setup(t_cmds *cmds)
{
	/*
	fd = 1 標準出力
	fd = 2 パイプ
	fd = 3 リダイレクト
	int	outfile_fd;

	ここでfdを入れ替える
	if (cmds->fd == STDOUT)
		return ;
	else if (cmds->fd == PIPE)
	{
		outfile_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
	}
	else if (cmds->fd == REDIRECT)
*/
}