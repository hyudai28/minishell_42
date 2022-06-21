/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:27:59 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/21 23:27:59 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_error(char *word)
{
	write(2, "minishell: warning: not found delimiter (wanted `", 49);
	ft_putstr_fd(word, 2);
	write(2, "')\n", 3);
}

int	heredoc_ctrl_c(char *temp, char *new_line)
{
	free(temp);
	free(new_line);
	return (1);
}
