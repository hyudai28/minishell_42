/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:14:30 by tarata            #+#    #+#             */
/*   Updated: 2022/05/30 22:53:09 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wrap(void **p, size_t len)
{
	*p = malloc(len);
	if (*p == NULL)
		return (0);
	return (1);
}

int	ft_wrap2(void ***p, size_t len)
{
	*p = malloc(len);
	if (*p == NULL)
		return (0);
	return (1);
}
