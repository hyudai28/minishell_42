#include "minishell.h"

int	lexer(char *argv, t_token *head)
{
	t_token	*cur;
	char	*str;

	str = argv;
	while (*str != '\0')
	{
		while (ft_isspace(*str))
			str++;
		cur = new_token();
		if (cur == NULL)
		{
			free(argv);
			token_destructor(head);//malloc error output
			return (1);
		}
		add_token_last(head, cur);
		get_token(cur, str);
		cur->word = (char *)malloc(sizeof(char) * cur->word_len + 1);
		if (cur->word == NULL)
		{
			free(argv);
			token_destructor(head);//malloc error output
			return (1);
		}
		ft_strlcpy(cur->word, str, cur->word_len + 1);
		str += cur->word_len;
	}
	free(argv);
	return (0);
}
