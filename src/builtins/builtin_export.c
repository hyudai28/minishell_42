/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:15:49 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/22 00:56:28 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_is_invalid(char *line)
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

static int	export_change(char *new_line, t_envlist *head)
{
	t_envlist	*env;
	char		*chr_pt;
	char		*str_key;

	chr_pt = ft_strchr(new_line, '=');
	if (!chr_pt)
	{
		env = envlist_search(new_line, head);
		if (!env)
			return (2);
	}
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

static int	key_check(char *cmds, t_envlist *head, int output)
{
	size_t	i;

	i = 0;
	while (cmds[i] != '\0' && cmds[i] != '=')
	{
		if (ft_isalnum(cmds[i]) != 1 && cmds[i] != '_')
		{
			if (output == 1)
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(cmds, 2);
				error("': not a valid identifier", 1, head);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

static int	export_add(char **cmds, int argc, t_envlist *head)
{
	int		arg_i;
	int		ret;
	int		ret_flag;
	int		err_flag;

	arg_i = 0;
	ret_flag = 0;
	err_flag = 0;
	while (++arg_i < argc)
	{
		if (ft_strchr(cmds[arg_i], '-') && arg_i != 2)
		{
			export_error(cmds[arg_i], EXPORT_IDENTIFIER);
			err_flag++;
		}
		ret = export_change(cmds[arg_i], head);
		if (ret == 1)
			err_flag += !error(strerror(errno), 1, head);
		if (ret == 2 && key_check(cmds[arg_i], head, 1) == 0)
			if (envlist_add(cmds[arg_i], head->prev, head) == 1)
			err_flag += error(strerror(errno), 1, head);
		if (ret_flag == 0)
			ret_flag = key_check(cmds[arg_i], head, 0);
	}
	return (ret_flag || err_flag);
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
