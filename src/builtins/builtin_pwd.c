
#include "../include/minishell.h"

int builtin_pwd(void)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
	write(1, pwd, ft_strlen(pwd));
	free(pwd);
	write(1, "\n", 1);
    return (0);
}