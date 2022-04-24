/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarata <tarata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 22:45:32 by tarata            #+#    #+#             */
/*   Updated: 2021/04/24 02:36:56 by tarata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_big(const char *str1, const char *to_find1)
{
	while (*to_find1)
	{
		if (*str1 != *to_find1)
			return (0);
		str1++;
		to_find1++;
	}
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!(*little))
		return ((char *)big);
	i = 0;
	while (i < len && *big)
	{
		if (ft_strlen(little) + i > len)
			break ;
		if (ft_check_big(big, little))
			return ((char *)big);
		big++;
		i++;
	}
	return (NULL);
}
