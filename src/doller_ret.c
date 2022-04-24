#include "include/minishell.h"

int	doller_ret(int ret, t_envlist *env)
{
	env->doller_ret = ret;
	return (ret);
}