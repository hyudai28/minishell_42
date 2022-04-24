NAME := minishell

CC := gcc
#CFLAGS := -Wall -Werror -Wextra -lreadline
CFLAGS := -Wall -Werror -Wextra  -L $(shell brew --prefix readline)/lib -lreadline -lhistory
INCLUDE                :=        -I $(shell brew --prefix readline)/include
# -g -fsanitize=address
SOURCE_DIR := src
BUILTIN_DIR := src/builtins

SRCS := $(SOURCE_DIR)/main.c
SRCS += $(SOURCE_DIR)/doller_ret.c
SRCS += $(SOURCE_DIR)/minishell_lexcer.c
SRCS += $(SOURCE_DIR)/minishell_parcer.c
SRCS += $(SOURCE_DIR)/minishell_excute.c
SRCS += $(SOURCE_DIR)/minishell_expansion.c
SRCS += $(SOURCE_DIR)/minishell_error.c
SRCS += $(SOURCE_DIR)/minishell_signal.c
SRCS += $(SOURCE_DIR)/minishell_utils.c
SRCS += $(SOURCE_DIR)/expansion_utils.c
SRCS += $(SOURCE_DIR)/t_cmds.c
SRCS += $(SOURCE_DIR)/t_token.c
SRCS += $(SOURCE_DIR)/t_envlist.c
SRCS += $(SOURCE_DIR)/list_show.c
SRCS += $(SOURCE_DIR)/token_strlen.c
SRCS += $(SOURCE_DIR)/read_lexcer.c

SRCS += $(BUILTIN_DIR)/builtin_cd.c
SRCS += $(BUILTIN_DIR)/builtin_echo.c
SRCS += $(BUILTIN_DIR)/builtin_env.c
SRCS += $(BUILTIN_DIR)/builtin_exit.c
SRCS += $(BUILTIN_DIR)/builtin_export.c
SRCS += $(BUILTIN_DIR)/builtin_pwd.c
SRCS += $(BUILTIN_DIR)/builtin_unset.c
SRCS += $(BUILTIN_DIR)/builtins.c

OBJS = ${SRCS:.c=.o}
BONUSOBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
		make -C libft
		$(CC) $(CFLAGS) ./libft/libft.a -o $(NAME) $(OBJS)

.c.o:
		$(CC) $(CFLAG) $(INCLUDE) -c $< -o $@ 

clean:
		rm -f $(OBJS) $(BONUSOBJS)
		make clean -C libft

fclean: clean
		rm -rf $(NAME)
		make fclean -C libft

re: fclean all

.PHONY: all clean fclean re