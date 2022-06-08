#ifndef T_ENVLIST_H
# define T_ENVLIST_H

# include <stdlib.h>
# include <stdbool.h>

# include "libft.h"

# include "t_token.h"

typedef struct s_envlist
{
	char					*key;
	char					*value;
	struct s_envlist		*next;
	struct s_envlist		*prev;
	bool					head;
	int						myself;
	int						doller_ret;
}		t_envlist;

//envlist.c
t_envlist	*envlist_constructor(char **envp);
void		envlist_destructor(t_envlist *envlist);
void		envlist_show(t_envlist *env);

//manage_envlist.c
int			envlist_add(char *new_line, t_envlist *prev, t_envlist *head);
t_envlist	*envlist_search(char *tr_line, t_envlist *node);
void		envlist_delete(char *delete_line, t_envlist *head);

//envlist_utils.c
int			envlist_set_keyvalue(t_envlist *target, char *new_line);
char		**envlist_to_key(t_envlist *head);
char	*envlist_get_key(char *line);
int	envlist_set_value(t_envlist *target, char *value_line);

#endif
