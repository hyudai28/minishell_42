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
		if (!cur)
			return (1);
	}
	if (!cur)
		return (1);
	free(argv);
	argv = NULL;
	return (0);
}
