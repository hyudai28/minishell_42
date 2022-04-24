#include "../include/minishell.h"

#define PATHNAME_SIZE 2048;
#define PWD 0;
#define ECHO 1;

int	builtins(char **cmds, t_envlist *env)
{
	int func;

	if (!ft_strncmp(cmds[0], "echo", 5))
		return (builtin_echo(cmds, env));
	else if (!ft_strncmp(cmds[0], "cd", 3))
		return (builtin_cd(cmds, env));
	else if (!ft_strncmp(cmds[0], "pwd", 4))
		return (builtin_pwd());
	else if (!ft_strncmp(cmds[0], "export", 7))
		return (builtin_export(env, cmds));
	else if (!ft_strncmp(cmds[0], "unset", 5))
		return (builtin_unset(env, cmds));
	else if (!ft_strncmp(cmds[0], "env", 4))
		return (builtin_env(cmds, env));
	else if (!ft_strncmp(cmds[0], "exit", 5))
		return (builtin_exit(cmds, char_count(cmds)));
	else
		return (command_excute(cmds, env));
}
