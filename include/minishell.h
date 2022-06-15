/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyudai <hyudai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 00:36:30 by mfujishi          #+#    #+#             */
/*   Updated: 2022/06/16 01:42:12 by hyudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<stdlib.h>
# include<string.h>
# include<ctype.h>
# include<stdbool.h>

# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "libft.h"
# include "get_next_line.h"
# include "t_token.h"
# include "t_cmds.h"
# include "t_envlist.h"

# define TRUE	1
# define SUCCESS	1
# define FALSE	0
# define ERROR	-1
# define EXPORT_IDENTIFIER 1
# define INVALID_OPTION 2
# define NO_SUCH_DIR	-3
# define NOT_A_DIR -4
# define PERMISSION_ERR	-5

volatile sig_atomic_t	g_signal_handled;

int		minishell(char *command, t_envlist *envp);

//lexer
int		lexer(char *argv, t_token *head, t_envlist *env);

//parser
int		parser(t_token *token, t_envlist *env);

//heredoc
int		heredocument(t_token *head, t_envlist *env);
int		heredoc_expansion(t_token *token, t_envlist *env);
char	*heredoc_expansion_line(char *expand_word, char *word, t_envlist *env);

//expansion
size_t	get_next_sq(char *word);
int		expansion(t_token *token, t_envlist *env);
int		expansion_env(t_token *token, t_envlist *env);
char	*expansion_line(char *expand_word, char *word, t_envlist *env);
int		remove_quot(t_token *token, t_envlist *env);
int		add_separate_token(t_token *token, t_envlist *env);
size_t	get_exit_status_digit(t_envlist *env);
char	*get_env_value(char *word, t_envlist *env);
char	*ft_strjoin3(char *a, char *b, char *c, int need_free);
size_t	get_envlen(const char *line);

//utils
int		char_count(char **count);
void	split_free(char **split);
int		doller_ret(int ret, t_envlist *env);

//execute
int		minishell_execute(t_cmds *cmds, t_envlist *envp);
char	*get_command_path(char **cmds, t_envlist *env);
int		pipex(t_envlist *env, char *path, t_cmds *cmd, int *backup_fd);
void	clean_fd(int close_fd, int backup_fd);
int		do_parent(void);
int		all_wait(t_cmds *cmds, t_envlist *env, int result, int *stdfd);

// int		set_backup_fd(int dup_fd, int stdfd);
int		pipe_setup(t_cmds *cmds, int *infd, int stdfd[2], t_envlist *env);
int		pipe_setfd(t_cmds *cmds, int *stdfd, int infd, t_envlist *env);

//debug
void	debug1(t_token *tmp);
void	debug_all(t_token *tmp);
void	debug_cmds(t_cmds *tmp);
void	debug_read(void);
void	debug2(t_token *tmp);

//error
int		error(char *msg, int error_no, t_envlist *env);
int		export_error(char *msg, int flag);

//builtins
int		builtins(char **cmds, t_envlist *env);
int		builtin_echo(char **cmds, int argc, t_envlist *env);
int		builtin_cd(char **cmds, int argc, t_envlist *env);
int		builtin_pwd(char **cmds, int argc, t_envlist *env);
int		builtin_export(char **cmds, int argc, t_envlist *env);
int		export_print(t_envlist *head);
int		builtin_unset(char **cmds, int argc, t_envlist *env);
int		builtin_env(char **cmds, int argc, t_envlist *env);
int		builtin_exit(char **exit_num, int argc, t_envlist *env);
int		exit_isspace(int c);

//command_execute
void	fd_setup(t_cmds *cmds);
int		command_execute(t_envlist *env, t_cmds *cmd, int *backup_fd);

//minishell_signal
int		minishell_signal(void);
int		execute_signal(void);

//struct
int		free_structors(t_token *token, t_cmds *cmds, t_envlist *env);

#endif
