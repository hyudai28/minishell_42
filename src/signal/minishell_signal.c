/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:43:10 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/12 00:53:26 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_ctrl_c(int sig)
{
	(void)sig;
	g_signal_handled = sig;
	write(1, "\b\b\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	perr_exit(char *err_msg)
{
	perror(err_msg);
	exit(1);
}

int	minishell_signal(void)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_bs;

	ft_memset(&ctrl_c, 0, sizeof(ctrl_c));
	ctrl_c.sa_handler = signal_ctrl_c;
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	ft_memset(&ctrl_bs, 0, sizeof(ctrl_bs));
	ctrl_bs.sa_handler = SIG_IGN;
	ctrl_bs.sa_flags = 0;
	if (sigemptyset(&ctrl_bs.sa_mask))
		perr_exit("emptyset");
	if (sigaction(SIGINT, &ctrl_c, NULL) < 0)
		perr_exit("sigaction");
	if (sigaction(SIGQUIT, &ctrl_bs, NULL) < 0)
		perr_exit("sigaction");
	return (0);
}

int	execute_signal(void)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_bs;

	ft_memset(&ctrl_c, 0, sizeof(ctrl_c));
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	ft_memset(&ctrl_bs, 0, sizeof(ctrl_bs));
	ctrl_bs.sa_handler = SIG_DFL;
	ctrl_bs.sa_flags = 0;
	if (sigemptyset(&ctrl_bs.sa_mask))
		perr_exit("emptyset");
	if (sigaction(SIGINT, &ctrl_c, NULL) < 0)
		perr_exit("sigaction");
	if (sigaction(SIGQUIT, &ctrl_bs, NULL) < 0)
		perr_exit("sigaction");
	return (0);
}
