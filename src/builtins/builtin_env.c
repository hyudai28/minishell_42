/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 21:27:29 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/06 00:17:12 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **cmds, int argc, t_envlist *envp)
{
	(void)cmds;
	(void)argc;
	if (!envp->next ||envp->next->head)
		return (0);
	envp = envp->next;
	while (envp->head != 1)
	{
		if (envp->value)
		{
			ft_putstr_fd(envp->key, 1);
			write(1, "=", 1);
			ft_putendl_fd(envp->value, 1);
		}
		envp = envp->next;
	}
	return (0);
}
