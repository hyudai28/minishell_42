/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 01:45:38 by mfujishi          #+#    #+#             */
/*   Updated: 2022/05/25 01:45:40 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exit_numeric(const char *num)
{
	ft_putstr_fd("minishell: exit: ", 2);
	write(2, num, ft_strlen(num));
	ft_putendl_fd(": numeric argument required", 2);
	exit (255);
}

static int	exit_atoi_overflow(unsigned long dest, int sign)
{
	unsigned long	max;

	max = 9223372036854775807;
	if (sign == 1)
	{
		if (dest > max)
			return (-1);
	}
	else if (sign == -1)
	{
		dest -= 1;
		if (dest > max)
			return (1);
	}
	return (0);
}

static int	check_number(const char *str)
{
	size_t	i;

	i = 0;
	while (ft_isdigit(*str))
	{
		str++;
		i++;
	}
	if (*str != '\0' && !ft_isdigit(*str))
		return (1);
	if (i >= 20)
		return (1);
	return (0);
}

static int	exit_atoi(const char *str)
{
	unsigned long	dest;
	int				sign;
	const char		*error_str;

	dest = 0;
	sign = 1;
	error_str = str;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	if (check_number(str) != 0)
		exit_numeric(error_str);
	while (ft_isdigit(*str))
	{
		dest = dest * 10 + *str - '0';
		str++;
	}
	if (exit_atoi_overflow(dest, sign) != 0)
		exit_numeric(error_str);
	return ((int)(dest * sign));
}

int	builtin_exit(char **exit_num, int argc, t_envlist *envp)
{
	unsigned int	ret;

	(void)envp;
	if (argc == 1)
		return (0);
	if (argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	ret = (unsigned int)exit_atoi(exit_num[1]);
	ft_putendl_fd("exit", 1);
	exit (ret % 256);
}
