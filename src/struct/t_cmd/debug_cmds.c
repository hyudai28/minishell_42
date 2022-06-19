/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 21:54:44 by hyudai            #+#    #+#             */
/*   Updated: 2022/06/19 22:29:51 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cmds.h"

void	print_outfd_type(enum e_cmds_out_fd outfd)
{
	if (outfd == FD_PIPE_OUT)
		printf("-outfd = FD_PIPE_OUT\n");
	else if (outfd == FD_REDIRECT)
		printf("-outfd = FD_REDIRECT\n");
	else if (outfd == FD_APPEND_REDIRECT)
		printf("-outfd = FD_APPEND_REDIRECT\n");
	else if (outfd == FD_STDOUT)
		printf("-outfd = FD_STDOUT\n");
}

void	print_infd_type(enum e_cmds_in_fd infd)
{
	if (infd == FD_HEAD)
		printf("-infd = FD_HEAD\n");
	else if (infd == FD_PIPE_IN)
		printf("-infd = FD_PIPE_IN\n");
	else if (infd == FD_R_STDIN)
		printf("-infd = FD_R_STDIN\n");
	else if (infd == FD_HEREDOC)
		printf("-infd = FD_HEREDOC\n");
	else if (infd == FD_STDIN)
		printf("-infd = FD_STDIN\n");
}

void debug_cmds(t_cmds *tmp)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while (tmp->head != 1)
	{
		printf("\n------cmds[%d]------\n", i);
		j = 0;
		while (tmp->cmd[j])
		{
			printf("-cmd[%d] = [%s][%p]\n", j, tmp->cmd[j], &tmp->cmd[j]);
			j++;
		}
		print_infd_type(tmp->infd_type);
		print_outfd_type(tmp->outfd_type);
		tmp = tmp->next;
		i++;
	}
}
