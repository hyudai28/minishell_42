/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarata <tarata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 23:27:11 by tarata            #+#    #+#             */
/*   Updated: 2020/11/08 21:13:37 by tarata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s;

	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
			return ((void *)(src + i));
		i++;
	}
	return (NULL);
}
