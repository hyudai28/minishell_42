/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 21:38:39 by hyudai            #+#    #+#             */
/*   Updated: 2022/06/11 23:42:08 by mfujishi         ###   ########.fr       */
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
