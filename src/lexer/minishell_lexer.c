#include "minishell.h"

int lexer(char *argv, t_token *head, t_flag *flag, t_envlist *env)
{
	t_token *cur;
	char *str;

	str = argv;
	cur = head;
	while (*str != '\0')
	{
		while (isspace(*str))
		{
			str++;
			flag->space = TRUE;
		}
		flag_set(flag, *str);
		cur = new_token(flag, cur, &str);
		if (cur->word_len == ERROR)
		{
			cur->type = 1;
			return (1);
		}
		flag->space = FALSE;
	}
	cur = new_token(flag, cur, &str);
	//t_token *tmp = head;
	//debug_all(head);
	//exit(1);
	return (0);
}
