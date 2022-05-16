#include "minishell.h"

int lexer(char *argv, t_token *head)
{
	t_flag flag;
	t_token *cur;
	char *str;

	str = argv;
	cur = head;
	flag = (t_flag){0};
	while (*str != '\0')
	{
		while (ft_isspace(*str))
		{
			str++;
			flag.space = TRUE;
		}
		flag_set(&flag, *str);
		cur = new_token(&flag, cur, &str);
		if (cur->word_len == WORD_LEN_ERROR)
		{
			cur->type = 1;
			return (1);
		}
		flag.space = FALSE;
	}
	cur = new_token(&flag, cur, &str);
	//t_token *tmp = head;
	//debug_all(head);
	//exit(1);
	return (0);
}
