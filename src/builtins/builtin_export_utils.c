/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 01:36:28 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/16 01:36:28 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_output(char *line, t_envlist *head)
{
	t_envlist	*node;

	ft_putstr("declare -x ");
	ft_putstr(line);
	node = envlist_search(line, head);
	write(1, "=\"", 2);
	ft_putstr(node->value);
	write(1, "\"\n", 2);
}

static bool	envpcmp(char *s1, char *s2)
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

static void	envlist_swap(char **envp, t_envlist *head)
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

int	export_print(t_envlist *head)
{
	char	**split;

	split = envlist_to_key(head);
	if (split == NULL)
		return (1);
	envlist_swap(split, head);
	split_free(split);
	return (0);
}
