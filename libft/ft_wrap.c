/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarata <tarata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 13:14:30 by tarata            #+#    #+#             */
/*   Updated: 2021/04/24 13:39:30 by tarata           ###   ########.fr       */
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
