/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 00:49:51 by mfujishi          #+#    #+#             */
/*   Updated: 2022/05/24 00:49:51 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_token.h"

char	*token_strjoin(char *cmd_line, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	if (cmd_line == NULL)
		len1 = 0;
	else
		len1 = ft_strlen(cmd_line);
	if (s2 == NULL)
		len2 = 0;
	else
		len2 = ft_strlen(s2);
	str = (char *)malloc((len1 + len2 + 1) * sizeof(char));//失敗ケア
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, cmd_line, len1);
	ft_memcpy((str + len1), s2, len2);
	str[len1 + len2] = '\0';
	free(cmd_line);
	cmd_line = NULL;
	return (str);
}

size_t	count_token(t_token *token)
{
	size_t	size;

	size = 0;
	while (token->type != PIPE && token->type != TAIL)
	{
		if (token_check_separate(token->type) == 1)
		{
			token = token->next->next;
			continue ;
		}
		size++;
		token = token->next;
	}
	return (size);
}
