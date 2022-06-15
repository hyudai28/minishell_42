/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_sq.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 23:19:45 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/13 23:19:45 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_next_sq(char *word)
{
	size_t	len;

	len = 0;
	while (word[len] != '\0' && word[len] != '\'')
	{
		len++;
	}
	return (len + 1);
}
