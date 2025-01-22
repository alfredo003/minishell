NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft

LIBFT_DIR = ./libs/libft

LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	src/main.c							\
		src/utils/free_memory.c						\
		src/inits.c		\
		src/execute/redir.c								\
		src/utils/readline.c						\
		src/utils/dup_env.c					\
		src/utils/dup_tokens.c						\
		src/tokens/utils.c					\
		src/execute/redir_and_exec.c					\
		src/execute/execute_builtin.c				\
		src/execute/execute_cmd.c					\
		src/tokens/ft_verifying_argument.c			\
		src/heredoc/heredoc.c				\
		src/heredoc/verifying.c				\
		src/tokens/return_str.c				\
		src/tokens/split_advenced.c					\
		src/tokens/split_advenced2.c				\
		src/tokens/gettokens.c				\
		src/tokens/process_tokens.c		\
		src/pipe/minipipe.c						\
		src/env/env_to_matrix.c					\
		src/builtins/ft_echo.c				\
		src/builtins/ft_cd.c					\
		src/builtins/ft_pwd.c				\
		src/builtins/ft_exit.c				\
		src/env/get_env_value.c		\
		src/env/expand_variables.c	\
		src/env/utils.c	\
		src/builtins/ft_export.c			\
		src/builtins/ft_unset.c			\
		src/builtins/ft_env.c				\
		src/env/ft_getenv.c			\
		src/env/handle_export.c		\
		src/utils/utils.c \
		src/utils/close_and_reset.c \
		src/utils/strjoin_free.c

OBJS = $(SRCS:.c=.o)

$(NAME):	$(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@clear

all:	$(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)
	clear

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	clear

re: fclean all

.PHONY: all clean fclean re
