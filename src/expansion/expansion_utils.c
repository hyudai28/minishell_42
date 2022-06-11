/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:42:30 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 22:24:11 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin3(char *a, char *b, char *c, int need_free)
{
	char	*ret1;
	char	*ret2;

	ret1 = ft_strjoin(a, b);
	if (ret1 == NULL)
	{
		if (need_free)
		{
			free(a);
			free(b);
			free(c);
		}
		return (NULL);
	}
	ret2 = ft_strjoin(ret1, c);
	free(ret1);
	if (need_free)
	{
		free(a);
		free(b);
		free(c);
	}
	return (ret2);
}

size_t	get_exit_status_digit(t_envlist *env)
{
	int		exit_status;
	size_t	digit;

	digit = 0;
	exit_status = env->doller_ret;
	if (exit_status == 0)
		return (1);
	while (exit_status != 0)
	{
		exit_status = exit_status / 10;
		digit++;
	}
	return (digit);
}
