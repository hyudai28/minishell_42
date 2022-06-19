/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmds.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 00:37:48 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/16 00:37:48 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CMDS_H
# define T_CMDS_H

# include <stdlib.h>

# include <fcntl.h>

# include "libft.h"

# include "t_token.h"

enum	e_cmds_out_fd
{
	FD_PIPE_OUT,
	FD_REDIRECT,
	FD_APPEND_REDIRECT,
	FD_STDOUT,
};

enum	e_cmds_in_fd
{
	FD_HEAD,
	FD_PIPE_IN,
	FD_R_STDIN,
	FD_HEREDOC,
	FD_STDIN,
};

typedef struct s_cmds
{
	char				**cmd;
	enum e_cmds_in_fd	infd_type;
	enum e_cmds_out_fd	outfd_type;
	int					infd;
	int					outfd;
	char				*heredoc_str;
	pid_t				pid;
	struct s_cmds		*next;
	struct s_cmds		*prev;
	bool				head;
}		t_cmds;

//cmds.c
t_cmds		*cmds_constructor(int head, t_cmds *cmd_head, t_cmds *now);
void		cmds_destructor(t_cmds *cmds);

//set_fd_cmds.c
t_cmds		*token_to_cmds(t_token *token);
t_token		*cmds_set_fd(t_cmds *new, t_token *token);
t_token		*set_type_infd(t_cmds *new, t_token *token);
t_token		*set_type_outfd(t_cmds *new, t_token *token);

void		debug_cmds(t_cmds *tmp);

#endif
