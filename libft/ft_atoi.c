/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:32:44 by tarata            #+#    #+#             */
/*   Updated: 2021/12/31 21:40:34 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char *str)
{
	if (*str == ' '
		|| *str == '\t'
		|| *str == '\r'
		|| *str == '\f'
		|| *str == '\v'
		|| *str == '\n')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	nbr;

	nbr = 0;
	sign = 1;
	while (ft_isspace(str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (int)*str - '0';
		str++;
	}
	return (nbr * sign);
}
