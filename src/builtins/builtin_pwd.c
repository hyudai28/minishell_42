/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 01:45:57 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/20 22:09:55 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_error(t_envlist *env)
{
	t_envlist	*pwd_node;

	pwd_node = envlist_search("PWD", env);
	if (!pwd_node)
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		error(strerror(errno), 1, env);
		return (1);
	}
	ft_putendl(pwd_node->value);
	return (0);
}

int	builtin_pwd(char **cmds, int argc, t_envlist *env)
{
	char	*pwd;

	(void)cmds;
	(void)argc;
	(void)env;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		return (pwd_error(env));
	}
	write(1, pwd, ft_strlen(pwd));
	free(pwd);
	write(1, "\n", 1);
	return (0);
}
