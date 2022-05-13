#include "minishell.h"

int error(char *msg, int error_no, t_envlist *env)
{
	env->doller_ret = error_no;
	ft_putendl_fd(msg, 2);
	return (0);
}

int	export_error(char *msg, int flag)
{
	ft_putstr_fd("minishell: export: ", 2);
	if (flag == EXPORT_IDENTIFIER)
	write(1, "\'", 1);
	ft_putstr_fd(msg, 2);
	if (flag == EXPORT_IDENTIFIER || ft_strlen(msg) == 1)
	{
		write(1, "\'", 1);
		ft_putstr_fd(msg, 2);
		write(1, "\'", 1);
		ft_putendl_fd(": not a valid identifier", 2);
	}
	else if (flag == INVALID_OPTION)
	{
		write(2, msg, 2);
		ft_putendl_fd(": invalid option", 2);
		ft_putendl_fd("export: usage: export [name[=value] ...]", 2);
	}
	return (flag);
}
//bad optionの再現ができない
