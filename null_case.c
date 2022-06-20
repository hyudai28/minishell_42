#include <unistd.h>

int	main(void)
{
	execve("./minishell", NULL, NULL);
}