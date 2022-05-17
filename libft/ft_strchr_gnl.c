#include "libft.h"

int	ft_strchr_gnl(char *str_stored, char c)
{
	int	i;

	i = 0;
	while (str_stored[i])
	{
		if (str_stored[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
