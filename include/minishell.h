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

// t_envlist *envp_head;

//lexer
int		lexer(char *argv, t_token *head);

//parser
int		parser(t_token *token, t_envlist *env);

//heredoc
int		heredocument(t_token *head);

//expansion
int		remove_quot(t_token *token);
int		expansion(t_token *token, t_envlist *env);
void	move_pointer(char **tmp, size_t len);
void	add_string_ex(t_token *token, t_flag *flag, char **tmp);
void	add_string(t_token *token, t_flag *flag, char **tmp);
void	add_string_dq(t_token *token, t_flag *flag, char **tmp, t_envlist *env);
void	add_dq_end(t_token *token, t_flag *flag, char **tmp);
void	add_dollar(t_token *token, t_flag *flag, char **tmp);
void	add_childprocess(\
	t_token *token, t_flag *flag, char **tmp, t_envlist *env);
int		expansion_dq(t_token *token, t_envlist *env);

//utils
int		char_count(char **count);
void	envsplit_free(char **split);
int		doller_ret(int ret, t_envlist *env);

//execute
int		minishell_execute(t_token *head, t_envlist *envp);
char	*get_command_path(char **cmds, t_envlist *env);
int		pipex(char **cmds, t_envlist *env, char *path);
int		pipe_setup(t_cmds *cmds, int *infd, int stdfd[2], t_envlist *env);
void	clean_fd(int *backup_fd);
void	set_backup_fd(int *stdfd);
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
int		builtin_unset(char **cmds, int argc, t_envlist *env);
int		builtin_env(char **cmds, int argc, t_envlist *env);
int		builtin_exit(char **exit_num, int argc, t_envlist *env);
int		exit_isspace(int c);

//command_execute
void	fd_setup(t_cmds *cmds);
int		command_execute(char **cmds, t_envlist *env);

//minishell_signal
int		minishell_signal(void);
int		execute_signal(void);

#endif
