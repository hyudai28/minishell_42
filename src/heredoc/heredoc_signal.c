/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 22:53:36 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/21 22:53:36 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_event_hook(void)
{
	if (g_signal_handled)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		g_signal_handled = 1;
		rl_done = true;
		rl_event_hook = NULL;
	}
	return (1);
}

int	hook_reset(void)
{
	rl_signal_event_hook = event_hook;
	rl_event_hook = NULL;
	rl_done = false;
	g_signal_handled = 0;
	return (1);
}
