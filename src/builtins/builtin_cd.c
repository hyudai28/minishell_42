/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfujishi <mfujishi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 01:46:04 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/17 19:17:09 by mfujishi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_homedir(t_envlist *env)
{
	t_envlist	*list;
	char		*oldpwd;
	int			dir_ret;

	list = envlist_search("PWD", env);
	oldpwd = ft_strdup(list->value);
	list = envlist_search("HOME", env);
	dir_ret = chdir(list->value);
	if (oldpwd == NULL)
		ft_putendl_fd("minishell: Cannot allocate memory", 2);
	else if (dir_ret == -1)
		ft_putendl_fd("bash: cd: HOME not set", 2);
	else
	{
		list = envlist_search("OLDPWD", env);
		if (!list)
			envlist_add(ft_strjoin("OLDPWD=", oldpwd), env->prev, env);
		else
		{
			free(list->value);
			list->value = ft_strdup(oldpwd);
		}
	}
	free(oldpwd);
	return (!!dir_ret);
}

int	cd_errors(char **cmds, int flag)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd("cd : ", 2);
	if (flag == INVALID_OPTION)
	{
		ft_putstr_fd(cmds[1], 2);
		ft_putendl_fd(": invalid option\ncd: usage: cd [dir]", 2);
	}
	else
	{
		ft_putstr_fd(cmds[1], 2);
		if (flag == NO_SUCH_DIR)
			ft_putendl_fd(": No such file or directory", 2);
		else if (flag == NOT_A_DIR)
			ft_putendl_fd(": Not a directory", 2);
		else if (flag == PERMISSION_ERR)
			ft_putendl_fd(": permission denied", 2);
	}
	return (1);
}

int	cd_dir_access(char **cmds, char *oldpwd)
{
	int			dir_ret;
	struct stat	stat_buf;

	dir_ret = chdir(cmds[1]);
	if (!dir_ret)
		return (0);
	if (stat(cmds[1], &stat_buf))
		cd_errors(cmds, NO_SUCH_DIR);
	else if (!(stat_buf.st_mode & S_IXUSR))
		cd_errors(cmds, PERMISSION_ERR);
	else if (S_ISDIR(stat_buf.st_mode))
		cd_errors(cmds, NOT_A_DIR);
	if (dir_ret == -1)
	{
		free(oldpwd);
		return (-2);
	}
	return (1);
}

static char	*get_pwd(t_envlist *list)
{
	char	*oldpwd;

	if (list == NULL || list->value == NULL)
		oldpwd = getcwd(NULL, 0);
	else
		oldpwd = ft_strdup(list->value);
	if (oldpwd == NULL)
	{
		ft_putendl_fd("minishell: Cannot allocate memory", 2);
		return (NULL);
	}
	return (oldpwd);
}

/*
bash: cd: -i: invalid option
cd: usage: cd [-L|-P] [dir]
*/

int	builtin_cd(char **cmds, int argc, t_envlist *env)
{
	char		*oldpwd;
	t_envlist	*list;
	int			dir_ret;

	(void)argc;
	if (argc == 1)
		return (go_homedir(env));
	else if (is_option(cmds[1]))
		return (cd_errors(cmds, INVALID_OPTION));
	list = envlist_search("PWD", env);
	oldpwd = get_pwd(list);
	if (oldpwd == NULL)
		return (1);
	dir_ret = cd_dir_access(cmds, oldpwd);
	if (dir_ret == -2)
		return (1);
	list = envlist_search("OLDPWD", env);
	if (list == NULL)
		return (0);
	free(list->value);
	list->value = ft_strdup(oldpwd);
	free(oldpwd);
	oldpwd = NULL;
	return (dir_ret);
}
