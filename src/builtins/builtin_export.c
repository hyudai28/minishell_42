/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:15:49 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 23:12:45 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	envpcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			if (((unsigned char)s1[i] - (unsigned char)s2[i]) > 0)
				return (0);
		else
			return (1);
		else
			i++;
	}
	if (!s1[i])
	{
		printf("s1 is null\n");
		return (1);
	}
	return (0);
}

void	export_output(char *line, t_envlist *head)
{
	t_envlist	*node;
	ft_putstr("declare -x ");
	ft_putstr(line);
	node = envlist_search(line, head);
	write(1, "=\"", 2);
	ft_putstr(node->value);
	write(1, "\"\n", 2);
}

void	envlist_swap(char **envp, t_envlist *head)
{
	char	*tmp;
	int		env_i;
	int		env_j;

	env_i = 0;
	tmp = NULL;
	while (envp[env_i])
	{
		env_j = env_i + 1;
		while (envp[env_j])
		{
			if (envpcmp(envp[env_j], envp[env_i]))
			{
				tmp = envp[env_j];
				envp[env_j] = envp[env_i];
				envp[env_i] = tmp;
			}
			env_j++;
		}
		export_output(envp[env_i], head);
		env_i++;
	}
}

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

int	export_print(t_envlist *head)
{
	char **split;

	split = envlist_to_key(head);
	if (split == NULL)
		return (1);
	envlist_swap(split, head);
	envsplit_free(split);
	return (0);
}

int	export_change(char *new_line, t_envlist *prev, t_envlist *head)
{
	t_envlist	*env;
	char	*chr_pt;
	char	*str_key;

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

int export_add(char **cmds, int argc, t_envlist *head)
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
			else
				head->prev->myself = 1;
		}
		arg_i++;
	}
	return (0);
}

int builtin_export(char **cmds, int argc, t_envlist *head)
{
	if (argc == 1)
	{
		printf("EXPORT print \n");
		return (export_print(head));
	}
	else if (export_is_invalid(cmds[1]))
	{
		printf("EXPORT ERR\n");
		return (export_error(cmds[1], INVALID_OPTION));
	}
	printf("EXPORT ADD\n");
	return (export_add(cmds, argc, head));
}
