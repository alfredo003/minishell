NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft

LIBFT_DIR = ./libs/libft

LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	src/main.c							\
		src/inits.c						\
		src/utils/readline.c						\
		src/utils/free_memory.c						\
		src/utils/dup_env.c					\
		src/redir_and_exec.c					\
		src/redir.c							\
		src/execute_builtin.c				\
		src/ft_verifying_argument.c			\
		src/execute_cmd.c					\
		src/increment_shell_level.c			\
		src/heredoc/heredoc.c				\
		src/cmd_tab.c						\
		src/tokens/ft_type.c					\
		src/tokens/return_str.c				\
		src/split_advenced.c					\
		src/split_advenced2.c				\
		src/tokens/get_separator.c			\
		src/tokens/gettokens.c				\
		src/tokens/process_str_utils.c		\
		src/tokens/process_str.c				\
		src/minipipe.c						\
		src/input.c							\
		src/numb_split.c						\
		src/ft_strisnum.c					\
		src/env_to_matrix.c					\
		src/add_envirenoment.c				\
		src/my_strndup.c						\
		src/builtins/ft_echo.c				\
		src/builtins/ft_cd.c					\
		src/builtins/ft_pwd.c				\
		src/builtins/ft_exit.c				\
		src/environment/get_env_value.c		\
		src/environment/expand_variables.c	\
		src/environment/expand_variables2.c	\
		src/environment/ft_export.c			\
		src/environment/ft_unset.c			\
		src/environment/ft_env.c				\
		src/environment/ft_getenv.c			\
		src/environment/handle_unset.c		\
		src/environment/handle_export.c		\
		src/ft_strjoin2.c					\
		src/sigquit.c						\
		src/ft_free_matrix.c					\
		src/verifying_heredoc.c				\
		src/dup_tokens.c						\
		src/ft_strcmp.c

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