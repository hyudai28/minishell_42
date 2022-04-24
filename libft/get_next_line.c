/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarata <tarata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 19:14:00 by tarata            #+#    #+#             */
/*   Updated: 2021/05/03 21:24:13 by tarata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_strdup_gnl(char *s)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_strlen_gnl(s);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	*ft_strjoin_gnl(char *line, char *str_stored, int n)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	int		i;

	len1 = ft_strlen_gnl(line);
	if (n >= 0)
		len2 = (size_t)n;
	else
		len2 = ft_strlen_gnl(str_stored);
	if (!ft_wrap((void **)&str, len1 + len2 + 1))
		return (NULL);
	i = -1;
	while (++i < (int)len1)
		str[i] = line[i];
	i = -1;
	while (++i < (int)len2)
		str[len1 + i] = str_stored[i];
	str[len1 + len2] = '\0';
	return (str);
}

int	ft_make_line(char **line, int fd, char *str_stored, char **buff_s)
{
	int		n;
	char	*tmp_line;
	char	*tmp_s;
	int		flag;

	tmp_s = NULL;
	flag = 0;
	n = ft_strchr_gnl(str_stored, '\n');
	tmp_line = ft_strjoin_gnl(*line, str_stored, n);
	if (tmp_line == NULL)
		return (-1);
	ft_reset_line(line, &tmp_line);
	if (n >= 0)
	{
		tmp_s = ft_strdup_gnl(str_stored + n + 1);
		if (tmp_s == NULL)
			return (-1);
		flag = 1;
	}
	free(buff_s[fd]);
	buff_s[fd] = tmp_s;
	return (flag);
}

int	ft_sub_get_next_line(int fd, char **line, int flag)
{
	ssize_t			ret;
	static char		*buff_s[FOPEN_MAX];
	char			*tmp_line;

	if (buff_s[fd])
		flag = ft_make_line(line, fd, buff_s[fd], buff_s);
	if (!ft_wrap((void **)&tmp_line, (size_t)BUFFER_SIZE + 1))
		return (-1);
	while (flag == 0)
	{
		ret = read(fd, tmp_line, BUFFER_SIZE);
		if (ret > 0)
		{
			tmp_line[ret] = '\0';
			flag = ft_make_line(line, fd, tmp_line, buff_s);
		}
		else
			break ;
	}
	free(tmp_line);
	if (ret < 0)
		return (ft_freeall(line, buff_s, fd));
	if (flag == 0)
		return (ft_free_static(buff_s, fd));
	return (flag);
}

int	get_next_line(int fd, char **line)
{
	int				flag;

	if (fd < 0 || FOPEN_MAX < fd || !line || BUFFER_SIZE <= 0)
		return (-1);
	flag = ft_memreset(line);
	if (flag == -1)
		return (-1);
	flag = ft_sub_get_next_line(fd, line, flag);
	return (flag);
}
