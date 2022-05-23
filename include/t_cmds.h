#ifndef T_CMD_H
# define T_CMD_H

# include <stdlib.h>

# include "libft.h"

# include "t_token.h"

enum	e_cmds_out_fd
{
	C_STDOUT,
	C_REDIRECT,
	C_PIPE,
	IN_PIPE,
	IN_REDIRECT,
};

typedef struct s_cmds
{
	char				**cmd;
	enum e_cmds_out_fd	outfd_type;
	char				*outfd_line;
	// bool	is_infile;
	struct s_cmds		*next;
	struct s_cmds		*prev;
	bool				head;
}		t_cmds;

//cmds.c
t_cmds		*cmds_constructor(int head, t_cmds *cmd_head);
void		cmds_destructor(t_cmds *cmds);

//set_fd_cmds.c
t_cmds		*token_to_cmds(t_token *token);

#endif
