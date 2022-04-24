
#include "./include/minishell.h"

int lexcer(char *argv, t_token *head, t_envlist *env)
{
	t_token *cur;
	t_flag flag;
	char *str;
	
	ft_memset(&flag, 0, sizeof(t_flag));
	str = argv;
	cur = head;
	while (*str != '\0')
	{
		while (isspace(*str))
		{
			str++;
			flag.space = TRUE;
		}
		flag_set(&flag, *str);
		cur = new_token(&flag, cur, &str);
		if (cur->word_len == ERROR)
		{
			cur->type = 1;
			return (1);
		}
		flag.space = FALSE;
	}
	cur = new_token(&flag, cur, &str);
	//t_token *tmp = head;
	if (!parcer(head, &flag, env))
		return (0);
	if (!expansion(head, &flag, env) || !expansion_q(head, &flag, env))
		return (0);
	//debug_all(head);
	//exit(1);
	return (0);
}

