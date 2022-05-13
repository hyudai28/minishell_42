#ifndef T_TOKEN_H
# define T_TOKEN_H
#include <stdlib.h>
# include <stdbool.h>
# include "libft.h"
// # include "./minishell.h"
#define TRUE	1
#define FALSE	0
#define ERROR	-1
typedef	enum
{
	HEAD,
	TAIL,
	EXPANDABLE_DQ,
	NONEXPANDABLE_SQ,
	EXPANDABLE,
	PIPE,
	REDIRECT,
	R_STDIN,
}	t_token_type;

typedef struct s_token
{
	struct s_token	*prev;
	struct s_token	*next;
	t_token_type	type;
	char			*word;
	size_t			word_len;
	int				space_flag;
	bool			head;
} t_token;

typedef	struct s_flag
{
	int	dq_flag;
	int sq_flag;
	int	pipe;
	int	redirect;
	int	error;
	int	space;
}	t_flag;

typedef	enum
{
	C_STDOUT,
	C_REDIRECT,
	C_PIPE,
	IN_PIPE,
	IN_REDIRECT,
}	t_cmds_out_fd;
typedef struct s_cmds
{
	char **cmd;
	t_cmds_out_fd	outfd_type;
	char	*outfd_line;
	// bool	is_infile;
	struct s_cmds *next;
	struct s_cmds *prev;
	bool	head;
}	t_cmds;

typedef struct s_envlist
{
	char *key;
	char *value;
	struct s_envlist *next;
	struct s_envlist *prev;
	bool	head;
	int		doller_ret;
}	t_envlist;

t_token *token_constructor();
void	token_destructor(t_token *token);
t_token *new_token(t_flag *flag, t_token *cur, char **str);
void	flag_set(t_flag *flag, char c);

//token_strlen.c
void ft_strlen_sq_dq(char *str, char quotation, t_token *new, t_flag *flag);
void ft_strlen_others(char *str, t_token *new);
void ft_strlen_redirect(char *str, t_token *new, t_flag *flag);
void ft_strlen_pipe(t_token *new, t_flag *flag);




t_cmds	*cmds_constructor(int head, t_cmds *cmd_head);
void	cmds_destructor(t_cmds *cmds);

t_cmds	*token_to_cmds(t_token *token);
char	*token_strjoin(char *cmd_line, char *s2);
bool	token_finish(t_token_type type);

t_envlist	*envlist_constructor(char **envp);
void	envlist_destructor(t_envlist *envlist);
void	envlist_delete(char *delete_line, t_envlist *head);
void	envlist_add(char *new_line, t_envlist *prev, t_envlist *head);
void	envlist_set_keyvalue(t_envlist *target, char *new_line);
t_envlist	*envlist_search(char *tr_line, t_envlist *node);
char	**envlist_to_char(t_envlist *head);



#endif