
#include "minishell.h"

int	echo_putout(char *line, int space)
{
	ft_putstr_fd(line, 1);
	if (space)
		write(1, " ", 1);
	return (0);
}

int	dollar_ret(char **cmds, t_envlist *env)
{
	if (!ft_strncmp(cmds[1], "$?", ft_strlen(cmds[1]) + 1))
	{
		printf("echo dollar ->%d¥n", env->doller_ret);
		env->doller_ret = 0;
		return (1);
	}
	return (0);
}

int builtin_echo(char **cmds, int argc, t_envlist *env)
{
	int i;

	(void)argc;
	if (cmds[1])
	{
		if (dollar_ret(cmds, env))
			return (0);
		if (!ft_strncmp(cmds[1], "-n", ft_strlen(cmds[1]) + 1))
		{
			i = 1;
			while (cmds[++i])
				echo_putout(cmds[i], !!cmds[i + 1]);
			return (0);
		}
		i = 1;
		while (cmds[i])
		{
			echo_putout(cmds[i], !!cmds[i + 1]);
			i++;
		}
	}
	ft_putendl_fd("", 1);
	env->doller_ret = 0;
	return (0);
}
