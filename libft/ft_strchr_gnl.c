/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_gnl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:45:13 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/14 22:45:14 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_gnl(char *str_stored, char c)
{
	int	i;

	i = 0;
	while (str_stored[i])
	{
		if (str_stored[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
