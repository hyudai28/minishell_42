#include "../include/minishell.h"

int	exit_numeric(const char *num)
{
	ft_putstr_fd("minishell: exit: ", 2);
	write(2, num, ft_strlen(num));
	ft_putendl_fd(": numeric argument required", 2);
	exit (255);
}

int	exit_isspace(int c)
{
	c = (char)c;
	if (('\t' <= c && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

static int	exit_atoi_error(const char *str, int flag)
{
	int		i;

	i = 0;
	while (ft_isdigit(*str))
	{
		str++;
		i++;
	}
	if (i >= 20)
		return (flag);
	return (0);
}

static int	exit_atoi_overflow(unsigned long dest, int flag)
{
	unsigned long	max;

	max = 9223372036854775807;
	if (flag == 1)
	{
		if (dest > max)
			return (-1);
	}
	else if (flag == -1)
	{
		dest -= 1;
		if (dest > max)
			return (1);
	}
	return (0);
}

static unsigned long	exit_atoi_execute(const char *str, unsigned long dest)
{
	while (ft_isdigit(*str))
	{
		if (!(ft_isdigit(*str)))
			break ;
		dest = dest * 10 + *str - '0';
		str++;
	}
	return (dest);
}

int	exit_atoi(const char *str)
{
	unsigned long	dest;
	int				flag;

	dest = 0;
	flag = 1;
	while (exit_isspace(*str))
		str++;
	if (*str == '-')
		flag = -1;
	if (*str == '+' || *str == '-')
		str++;
	if (exit_atoi_error(str, flag) == 1)
		exit_numeric(str);
	else if (exit_atoi_error(str, flag) == -1)
		exit_numeric(str);
	dest = exit_atoi_execute(str, dest);
	if (exit_atoi_overflow(dest, flag) == -1)
		exit_numeric(str);
	else if (exit_atoi_overflow(dest, flag) == 1)
		exit_numeric(str);
	return ((int)(dest * flag));
}

int	builtin_exit(char **exit_num, int argc, t_envlist *envp)
{
	unsigned int	ret;

	(void)argc;
	(void)envp;
	if (argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (argc == 1)
		ret = 0;
	else
		ret = (unsigned int)exit_atoi(exit_num[1]);
	ft_putendl_fd("exit", 1);
	exit (ret % 256);
}
