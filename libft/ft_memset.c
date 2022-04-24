/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarata <tarata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:07:34 by tarata            #+#    #+#             */
/*   Updated: 2020/11/11 22:19:52 by tarata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	src;

	dst = (unsigned char *)s;
	src = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		dst[i] = src;
		i++;
	}
	return (s);
}
