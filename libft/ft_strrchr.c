/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarata <tarata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 01:28:45 by tarata            #+#    #+#             */
/*   Updated: 2020/11/29 02:25:41 by tarata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	chr;
	size_t			len;

	chr = (unsigned char)c;
	len = ft_strlen(s);
	if (chr == '\0')
		return ((char *)&s[len]);
	while (len > 0)
	{
		len--;
		if (s[len] == chr)
			return ((char *)&s[len]);
	}
	if (s[0] == chr)
		return ((char *)s);
	return (NULL);
}
