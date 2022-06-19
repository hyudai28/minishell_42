/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 21:24:02 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/19 22:39:33 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_putout(char *line, int space)
{
	ft_putstr_fd(line, 1);
	if (space)
		write(1, " ", 1);
	return (0);
}

int	echo_check_flag(char *flag)
{
	size_t	flag_len;
	size_t	len_index;

	flag_len = ft_strlen(flag);
	len_index = 2;
	if (!ft_strncmp(flag, "-n", 2))
	{
		while (len_index < flag_len)
		{
			if (flag[len_index] == 'n')
				len_index++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

int	builtin_echo(char **cmds, int argc, t_envlist *env)
{
	int	i;

	(void)argc;
	if (cmds[1])
	{
		i = 1;
		if (echo_check_flag(cmds[i]))
		{
			while (cmds[i] && echo_check_flag(cmds[i]))
				i++;
			while (cmds[i])
			{
				echo_putout(cmds[i], !!cmds[i + 1]);
				i++;
			}
			return (0);
		}
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
