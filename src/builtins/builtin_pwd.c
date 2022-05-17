#include "minishell.h"

int	builtin_pwd(char **cmds, int argc, t_envlist *env)
{
	char	*pwd;

	(void)cmds;
	(void)argc;
	(void)env;
	pwd = getcwd(NULL, 0);
	write(1, pwd, ft_strlen(pwd));
	free(pwd);
	write(1, "\n", 1);
	return (0);
}
