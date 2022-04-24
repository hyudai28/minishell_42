/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarata <tarata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:42:49 by tarata            #+#    #+#             */
/*   Updated: 2021/05/03 19:21:22 by tarata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <unistd.h>
# include <stdlib.h>
# include <ulimit.h>
# include <limits.h>
# include <stdio.h>

int		get_next_line(int fd, char **line);
int		ft_make_line(char **line, int fd, char *str_stored, char **buff_s);
char	*ft_strjoin_gnl(char *line, char *str_stored, int n);
char	*ft_strdup_gnl(char *s);
int		ft_strchr_gnl(char *str_stored, char c);
int		ft_freeall(char **line, char **buf_s, int fd);
size_t	ft_strlen_gnl(char *s);
int		ft_memreset(char **line);
int		ft_free_static(char **buff_s, int fd);
void	ft_reset_line(char **line, char **tmp_line);
int		ft_sub_get_next_line(int fd, char **line, int flag);

#endif
