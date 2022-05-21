#include "minishell.h"

int	lexer(char *argv, t_token *head)
{
	t_flag	flag;
	t_token	*cur;
	char	*str;

	str = argv;
	cur = head;
	flag = (t_flag){0};
	while (*str != '\0')
	{
		while (ft_isspace(*str))
			str++;
		flag_set(&flag, *str);
		cur = new_token(&flag, cur, &str);
	}
	cur = end_token(cur);
	return (0);
}
