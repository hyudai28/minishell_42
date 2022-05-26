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
		flag_set(&flag, *str);
		cur = new_token(&flag, cur, &str);
		if (!cur)
			return (NULL);
	}
	cur = end_token(cur);
	if (!cur)
		return (NULL);
	free(argv);
	argv = NULL;
	return (0);
}
