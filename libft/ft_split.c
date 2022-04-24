/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarata <tarata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:26:47 by tarata            #+#    #+#             */
/*   Updated: 2021/04/24 13:55:42 by tarata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_make_array(char *str, char const *s, char c)
{
	while (*s != c && *s)
	{
		*str = *s;
		str++;
		s++;
	}
	*str = '\0';
}

static size_t	ft_word_count(char const *s, char c)
{
	size_t	word;
	size_t	i;

	i = 0;
	word = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
			i++;
		word++;
	}
	return (word);
}

static void	**str_free(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static size_t	word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		word;
	char	**str;
	int		i;

	if (s == NULL)
		return (NULL);
	word = ft_word_count(s, c);
	if (!ft_wrap2((void ***)&str, (sizeof(char *) * (word +1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != c && *s)
		{
			if (!ft_wrap((void **)&str[i], (word_len(s, c) + 1)))
				return ((char **)str_free(str));
			ft_make_array(str[i], s, c);
			s = s + word_len(s, c);
			i++;
		}
	}
	str[i] = NULL;
	return (str);
}
