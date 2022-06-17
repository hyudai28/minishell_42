/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 01:41:26 by hyudai            #+#    #+#             */
/*   Updated: 2022/06/17 13:03:51 by mfujishi         ###   ########.fr       */
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
	if (cmds == NULL)
		return (1);
	token_destructor(head);
	if (cmds->next->cmd[0] == NULL)
		return (0);
	result = minishell_execute(cmds, envp);
	return (doller_ret(result, envp));
}
