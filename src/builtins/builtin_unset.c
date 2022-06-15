/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 01:46:00 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/13 01:46:01 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **cmds, int argc, t_envlist *head)
{
	char	*delete;

	(void)argc;
	if (cmds[1])
	{
		delete = cmds[1];
		envlist_delete(delete, head);
	}
	return (0);
}
