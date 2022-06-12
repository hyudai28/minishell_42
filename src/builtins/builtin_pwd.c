/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 01:45:57 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/13 01:45:58 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
