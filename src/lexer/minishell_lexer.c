/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 22:39:48 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/12 01:05:25 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexer_error(void *p, char *argv, t_token *head, t_envlist *env)
{
	if (p == NULL)
	{
		free(argv);
		token_destructor(head);
		error("minishell: Cannot allocate memory", 1, env);
		return (1);
	}
	return (0);
}

int	lexer(char *argv, t_token *head, t_envlist *env)
{
	t_token	*cur;
	char	*str;

	str = argv;
	while (ft_isspace(*str))
		str++;
	while (*str != '\0')
	{
		cur = new_token();
		if (lexer_error(cur, argv, head, env) == 1)
			return (1);
		add_token_last(head, cur);
		get_token(cur, str);
		cur->word = (char *)malloc(sizeof(char) * cur->word_len + 1);
		if (lexer_error(cur->word, argv, head, env) == 1)
			return (1);
		ft_strlcpy(cur->word, str, cur->word_len + 1);
		str += cur->word_len;
		while (ft_isspace(*str))
			str++;
	}
	free(argv);
	return (0);
}
