#include "minishell.h"

int	lexer(char *argv, t_token *head)
{
	t_token	*cur;
	char	*str;

	str = argv;
	cur = head;
	while (*str != '\0')
	{
		while (ft_isspace(*str))
			str++;
		cur = new_token(cur, &str);
	}
	cur = end_token(cur);
	return (0);
}
