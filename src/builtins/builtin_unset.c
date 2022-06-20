/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 01:46:00 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/20 13:29:29 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **cmds, int argc, t_envlist *head)
{
	char	*delete;
	int		unset_index;

	unset_index = 1;
	while (unset_index < argc)
	{
		delete = cmds[unset_index];
		envlist_delete(delete, head);
		unset_index++;
	}
	return (0);
}
