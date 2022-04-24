/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:14:53 by tarata            #+#    #+#             */
/*   Updated: 2021/12/26 23:28:53 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int	ft_free_static(char **buff_s, int fd)
{
	free(buff_s[fd]);
	buff_s[fd] = NULL;
	return (0);
}

int	ft_memreset(char **line)
{
	*line = (char *)malloc(1);
	if (*line == NULL)
		return (-1);
	*line[0] = '\0';
	return (0);
}

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_freeall(char **line, char **buf_s, int fd)
{
	free(*line);
	*line = NULL;
	free(buf_s[fd]);
	buf_s[fd] = NULL;
	return (-1);
}

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
