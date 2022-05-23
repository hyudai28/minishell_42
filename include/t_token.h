#ifndef T_TOKEN_H
# define T_TOKEN_H

# include <stdlib.h>
# include <stdbool.h>

# include "libft.h"

# define TRUE	1
# define FALSE	0
# define WORD_LEN_ERROR	0
# define ERROR -1

enum	e_token_type
{
	HEAD,
	TAIL,
	EXPANDABLE_DQ,
	NONEXPANDABLE_SQ,
	EXPANDABLE,
	PIPE,
	REDIRECT,
	R_STDIN,
	HEREDOC,
};

typedef struct s_token
{
	struct s_token		*prev;
	struct s_token		*next;
	enum e_token_type	type;
	char				*word;
	size_t				word_len;
	int					space_flag;
	bool				head;
}		t_token;

typedef struct s_flag
{
	int	dq_flag;
	int	sq_flag;
	int	pipe;
	int	redirect;
	int	error;
	int	space;
}		t_flag;

//token.c
t_token		*token_constructor(void);
void		token_destructor(t_token *token);
size_t		count_token(t_token *token);
int			token_check_separate(enum e_token_type type);

//get_token.c
void	get_token(t_token *new, t_flag *flag, char **str);

//manage_token.c
t_token		*new_token(t_flag *flag, t_token *cur, char **str);
t_token		*end_token(t_token *cur);
int			token_delone(t_token *token);
void		flag_set(t_flag *flag, char c);
char		*token_strjoin(char *cmd_line, char *s2);

//token_utils.c
char	*token_strjoin(char *cmd_line, char *s2);
char	**separate_token(t_token *token);

#endif
