/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:38:39 by hyudai            #+#    #+#             */
/*   Updated: 2022/05/26 21:42:38 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_structors(t_token *token, t_cmds *cmds, t_envlist *env)
{
	if (token)
	{
		token_destructor(token);
		token = NULL;
	}
	if (cmds)
	{
		cmds_destructor(cmds);
		cmds = NULL;
	}
	if (env)
	{
		envlist_destructor(env);
		env = NULL;
	}
	return (1);
}