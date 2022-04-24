/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarata <tarata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:36:25 by tarata            #+#    #+#             */
/*   Updated: 2021/04/24 02:41:42 by tarata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_putarray(char *str, int len, long n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		str[i] = '-';
		n *= -1;
		i++;
	}
	while (i + 0 < len)
	{
		str[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	abs;

	len = 0;
	abs = n;
	if (abs == 0)
		len = 1;
	if (abs < 0)
	{
		abs *= -1;
		len++;
	}
	while (abs >= 1)
	{
		abs /= 10;
		len++;
	}
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str = ft_putarray(str, len, n);
	str[len] = '\0';
	return (str);
}
