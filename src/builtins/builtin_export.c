
#include "../include/minishell.h"

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
		printf("si is null\n");
		return (1);
	}
	return(0);
}



void	export_output(char *line, t_envlist *head)
{
	t_envlist *node;

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

int	builtin_export(t_envlist *head, char **cmds)
{
	char	**split;
	int		argc;
	int		arg_i;

	argc =  char_count(cmds);
	if (argc == 1)
	{
		split = envlist_to_char(head);
		envlist_swap(split, head);
	}
	else if (export_is_invalid(cmds[1]))
		export_error(cmds[1], INVALID_OPTION);
	arg_i = 1;
	while (arg_i < argc)
	{
		if (ft_strchr(cmds[arg_i], '-') && arg_i != 2)
			export_error(cmds[arg_i], EXPORT_IDENTIFIER);
		else
			envlist_add(cmds[arg_i], head->prev, head);
		arg_i++;
	}
	return (SUCCESS);
}