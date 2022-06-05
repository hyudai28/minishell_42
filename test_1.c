#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	execve("./minishell", NULL, NULL);
}