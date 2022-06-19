/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 01:41:26 by hyudai            #+#    #+#             */
/*   Updated: 2022/06/19 14:04:21 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"	//still reachable 218 blocks

int	minishell(char *command, t_envlist *envp)
{
	t_token	*head;
	t_cmds	*cmds;
	int		result;

	head = token_constructor();
	if (lexer(command, head, envp) == 1)
		return (1);
	if (parser(head, envp) == 1)
		return (1);
	if (heredocument(head, envp) == 1)
		return (1);
	if (expansion(head, envp) == 1)
		return (1);
	if (head->next == NULL)
		return (doller_ret(0, envp));
	cmds = token_to_cmds(head);
	token_destructor(head);
	if (cmds == NULL)
		return (1);
	result = minishell_execute(cmds, envp);
	return (doller_ret(result, envp));
}
