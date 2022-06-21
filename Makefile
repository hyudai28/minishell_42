NAME = minishell
LIB_DIR = libft/
LIBFT = libft.a

# Config
# ****************************************************************************

CC = gcc
CFLAGS := -L $(shell brew --prefix readline)/lib -lreadline -lhistory -Wall -Wextra -Werror #-g -fsanitize=address
OBJ_FLAG = -I include/ -I $(LIB_DIR) -I $(shell brew --prefix readline)/include -Wall -Wextra -Werror #-g -fsanitize=address
#CFLAGS = -L $(shell brew --prefix readline)/lib $(INCLUDE)
#INCLUDE = -I $(shell brew --prefix readline)/include -I include/ -I $(LIB_DIR)
DEBUG = -g -fsanitize=address
LIBFLAGS = -L $(LIB_DIR) -lft -lreadline -lhistory
#LIBFLAGS = -L $(LIB_DIR) -lft -lreadline -ltinfo

# Source files
# ****************************************************************************

MAIN_DIR	=	main/
MAIN_FILES	=	main.c \
				minishell.c \
				doller_ret.c \
				minishell_utils.c
MAIN_SRCS	=	$(addprefix $(MAIN_DIR), $(MAIN_FILES))

BUILTIN_DIR	=	builtins/
BUILTIN_FILES	=	builtin_cd.c \
				builtin_cd_utils.c \
				builtin_echo.c \
				builtin_env.c \
				builtin_exit.c \
				builtin_export.c \
				builtin_pwd.c \
				builtin_unset.c \
				builtins.c \
				builtin_export_utils.c
BUILTIN_SRCS	=	$(addprefix $(BUILTIN_DIR), $(BUILTIN_FILES))

ERROR_DIR	=	error/
ERROR_FILES	=	minishell_error.c
ERROR_SRCS	=	$(addprefix $(ERROR_DIR), $(ERROR_FILES))

EXECUTE_DIR	=	execute/
EXECUTE_FILES	=	minishell_execute.c \
					get_command_path.c \
					pipe_setup.c \
					pipex.c \
					all_wait.c
EXECUTE_SRCS	=	$(addprefix $(EXECUTE_DIR), $(EXECUTE_FILES))

EXPANSION_DIR	=	expansion/
EXPANSION_FILES	=	expansion_utils.c \
					minishell_expansion.c \
					expansion_line.c \
					remove_quot.c \
					add_separate_token.c \
					expansion_env.c \
					get_env_value.c \
					get_next_sq.c
EXPANSION_SRCS	=	$(addprefix $(EXPANSION_DIR), $(EXPANSION_FILES))

LEXER_DIR	=	lexer/
LEXER_FILES	=	minishell_lexer.c
LEXER_SRCS	=	$(addprefix $(LEXER_DIR), $(LEXER_FILES))

PARSER_DIR	=	parser/
PARSER_FILES	=	minishell_parser.c
PARSER_SRCS	=	$(addprefix $(PARSER_DIR), $(PARSER_FILES))

HEREDOC_DIR =	heredoc/
HEREDOC_FILES	=	heredoc.c \
					heredoc_expansion.c \
					heredoc_expansion_line.c
HEREDOC_SRCS	=	$(addprefix $(HEREDOC_DIR), $(HEREDOC_FILES))

SIGNAL_DIR	=	signal/
SIGNAL_FILES	=	minishell_signal.c
SIGNAL_SRCS	=	$(addprefix $(SIGNAL_DIR), $(SIGNAL_FILES))

STRUCT_DIR	=	struct/
STRUCT_FILES	=	free_structors.c
STRUCT_SRCS	=	$(addprefix $(STRUCT_DIR), $(STRUCT_FILES))

T_CMD_DIR	=	struct/t_cmd/
T_CMD_FILES	=	cmds.c \
				set_fd_cmds.c \
				set_type_infd.c \
				set_type_outfd.c \
				token_to_cmds.c
T_CMD_SRCS	=	$(addprefix $(T_CMD_DIR), $(T_CMD_FILES))

T_ENVLIST_DIR	=	struct/t_envlist/
T_ENVLIST_FILES	=	envlist.c \
					envlist_utils.c \
					manage_envlist.c \
					envlist_add.c \
					envlist_get.c
T_ENVLIST_SRCS	=	$(addprefix $(T_ENVLIST_DIR), $(T_ENVLIST_FILES))

T_TOKEN_DIR	=	struct/t_token/
T_TOKEN_FILES	=	token.c \
					token_utils.c \
					get_token.c \
					manage_token.c
T_TOKEN_SRCS	=	$(addprefix $(T_TOKEN_DIR), $(T_TOKEN_FILES))

SRC_FILES =			$(MAIN_SRCS) \
					$(BUILTIN_SRCS) \
					$(ERROR_SRCS) \
					$(EXECUTE_SRCS) \
					$(EXPANSION_SRCS) \
					$(LEXER_SRCS) \
					$(PARSER_SRCS) \
					$(HEREDOC_SRCS) \
					$(SIGNAL_SRCS) \
					$(STRUCT_SRCS) \
					$(T_CMD_SRCS) \
					$(T_ENVLIST_SRCS) \
					$(T_TOKEN_SRCS)

# addprefix

SRC_DIR = src/

OBJ_DIR = obj/
OBJS = $(SRC_FILES:%.c=$(OBJ_DIR)%.o)
MAIN_OBJS = $(MAIN_FILES:%.c=$(OBJ_DIR)main/%.o)
BUILTIN_OBJS = $(BUILTIN_FILES:%.c=$(OBJ_DIR)builtin/%.o)
ERROR_OBJS = $(ERROR_FILES:%.c=$(OBJ_DIR)error/%.o)
EXECUTE_OBJS = $(EXECUTE_FILES:%.c=$(OBJ_DIR)execute/%.o)
EXPANSION_OBJS = $(EXPANSION_FILES:%.c=$(OBJ_DIR)expansion/%.o)
LEXER_OBJS = $(LEXER_FILES:%.c=$(OBJ_DIR)lexer/%.o)
PARSER_OBJS = $(PARSER_FILES:%.c=$(OBJ_DIR)parser/%.o)
HEREDOC_OBJS = $(HEREDOC_FILES:%.c=$(OBJ_DIR)heredoc/%.o)
SIGNAL_OBJS = $(SIGNAL_FILES:%.c=$(OBJ_DIR)signal/%.o)
STRUCT_OBJS = $(STRUCT_FILES:%.c=$(OBJ_DIR)struct/%.o)
T_CMD_OBJS = $(T_CMD_FILES:%.c=$(OBJ_DIR)t_cmd/%.o)
T_ENVLIST_OBJS = $(T_ENVLIST_FILES:%.c=$(OBJ_DIR)t_envlist/%.o)
T_TOKEN_OBJS = $(T_TOKEN_FILES:%.c=$(OBJ_DIR)t_token/%.o)


# Recipe
# ****************************************************************************

all: $(NAME)

#$(NAME): $(OBJS)
#	make -C $(LIB_DIR)
#	$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)

#$(OBJS): $(OBJ_DIR)

#$(OBJ_DIR)%.o: $(SRC_DIR)%.c
#	$(CC) $(CFLAGS) -c $< -o $@
$(NAME): $(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)
$(OBJS): $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(OBJ_FLAG) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)$(MAIN_DIR)
	mkdir -p $(OBJ_DIR)$(BUILTIN_DIR)
	mkdir -p $(OBJ_DIR)$(ERROR_DIR)
	mkdir -p $(OBJ_DIR)$(EXECUTE_DIR)
	mkdir -p $(OBJ_DIR)$(EXPANSION_DIR)
	mkdir -p $(OBJ_DIR)$(LEXER_DIR)
	mkdir -p $(OBJ_DIR)$(PARSER_DIR)
	mkdir -p $(OBJ_DIR)$(HEREDOC_DIR)
	mkdir -p $(OBJ_DIR)$(SIGNAL_DIR)
	mkdir -p $(OBJ_DIR)$(STRUCT_DIR)
	mkdir -p $(OBJ_DIR)$(T_CMD_DIR)
	mkdir -p $(OBJ_DIR)$(T_ENVLIST_DIR)
	mkdir -p $(OBJ_DIR)$(T_TOKEN_DIR)

#debug: $(LIBFT) $(OBJS)
debug: $(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(DEBUG) $(LIBFLAGS) $(OBJS) -o $(NAME)

clean:
	make clean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR)
	rm -fr *.dSYM

fclean:
	make fclean -C $(LIB_DIR)
	rm -rf $(NAME) $(OBJ_DIR)
	rm -fr *.dSYM

re: fclean all
.PHONY: all clean fclean re
