/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarata <tarata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:09:48 by tarata            #+#    #+#             */
/*   Updated: 2020/11/28 01:27:13 by tarata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	size_d;
	size_t	size_s;
	size_t	i;

	size_d = ft_strlen(dst);
	size_s = ft_strlen(src);
	if (n <= size_d)
		return (n + size_s);
	i = 0;
	while (i < n - size_d - 1 && src[i])
	{
		dst[size_d + i] = src[i];
		i++;
	}
	dst[size_d + i] = '\0';
	return (size_d + size_s);
}
