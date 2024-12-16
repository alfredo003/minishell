NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft

LIBFT_DIR = ./libs/libft

LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	./srcs/minishell.c			\
	./srcs/environment/environment_utils.c 	\
	./srcs/utils.c				\
	./srcs/tokens/tokens.c			\
	./srcs/tokens/parse_tokens.c

OBJS = $(SRCS:.c=.o)

$(NAME):	$(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@sleep 1
	clear

all:	$(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@sleep 1
	clear

re: fclean all

.PHONY: all clean fclean re
