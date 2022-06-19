/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 01:46:00 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/19 18:04:27 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **cmds, int argc, t_envlist *head)
{
	char	*delete;
	int		unset_index;

//	(void)argc;
	unset_index = 1;
	while (unset_index < argc)
	{
		delete = cmds[unset_index];
		envlist_delete(delete, head);
		unset_index++;
	}
	return (0);
}
