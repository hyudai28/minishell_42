/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:15:49 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/12 15:38:36 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_is_invalid(char *line)
{
	if (line[0] == '-' || line[0] == '='
		|| line[0] == '+' || line[0] == '*'
		|| line[0] == '?' || line[0] == '~'
		|| line[0] == '^')
		return (1);
	else if (ft_isdigit(line[0]))
		return (1);
	return (0);
}

int	export_change(char *new_line, t_envlist *prev, t_envlist *head)
{
	t_envlist	*env;
	char		*chr_pt;
	char		*str_key;

	(void)prev;
	chr_pt = ft_strchr(new_line, '=');
	if (!chr_pt)
		return (0);
	else
	{
		str_key = envlist_get_key(new_line);
		if (!str_key)
			return (1);
		env = envlist_search(str_key, head);
		free(str_key);
		str_key = NULL;
		if (!env)
			return (2);
		else if (envlist_set_value(env, chr_pt + 1))
			return (1);
	}
	return (0);
}

int	export_add(char **cmds, int argc, t_envlist *head)
{
	int		arg_i;
	int		ret;

	arg_i = 1;
	while (arg_i < argc)
	{
		if (ft_strchr(cmds[arg_i], '-') && arg_i != 2)
			return (export_error(cmds[arg_i], EXPORT_IDENTIFIER));
		ret = export_change(cmds[arg_i], head->prev, head);
		if (ret == 1)
			return (error(strerror(errno), 1, head));
		if (ret == 2)
		{
			if (envlist_add(cmds[arg_i], head->prev, head) == 1)
				return (error(strerror(errno), 1, head));
		}
		arg_i++;
	}
	return (0);
}

int	builtin_export(char **cmds, int argc, t_envlist *head)
{
	if (argc == 1)
	{
		return (export_print(head));
	}
	else if (export_is_invalid(cmds[1]))
	{
		return (export_error(cmds[1], INVALID_OPTION));
	}
	return (export_add(cmds, argc, head));
}
