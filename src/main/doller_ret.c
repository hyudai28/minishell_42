/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doller_ret.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:31:05 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 15:31:06 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	doller_ret(int ret, t_envlist *env)
{
	env->doller_ret = ret;
	return (ret);
}
