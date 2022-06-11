/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:33:36 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/11 18:33:36 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pathjoin(char *bin_path, char *cmd, t_envlist *env)
{
	char	*add_slash;
	char	*ret_path;

	add_slash = ft_strjoin(bin_path, "/"); //malloc
	if (!add_slash)
		error(strerror(errno), 1, env);
	ret_path = ft_strjoin(add_slash, cmd); //malloc
	free(add_slash);
	add_slash = NULL;
	if (!ret_path)
		error(strerror(errno), 1, env);
	return (ret_path);
}

char	*set_command(char *cmd, char **bin_path, t_envlist *env)
{
	int		path_i;
	int		access_ret;
	char	*path;

	path_i = 0;
	access_ret = access(cmd, X_OK);
	if (access_ret == 0)
		return (ft_strdup(cmd)); //malloc
	while (bin_path[path_i])
	{
		path = ft_pathjoin(bin_path[path_i], cmd, env);
		access_ret = access(path, X_OK);
		if (access_ret == 0)
			return (path);
		free(path);
		path = NULL;
		path_i++;
	}
	return (NULL);
}

char	*get_command_path(char **cmds, t_envlist *env)
{
	t_envlist	*path_node;
	char		**path_split;
	char		*ret_path;

	path_node = envlist_search("PATH", env);
	if (path_node == NULL)
		return (NULL);
	path_split = ft_split(path_node->value, ':'); //malloc
	ret_path = set_command(cmds[0], path_split, env);
	envsplit_free(path_split);
	return (ret_path);
}
