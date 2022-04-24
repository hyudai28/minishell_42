#include "./include/minishell.h"

int	char_count(char **count)
{
	int	ret;

	ret = 0;
	while (count[ret])
		ret++;
	return (ret);
}

void	envsplit_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}