NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibft

LIBFT_DIR = ./libs/libft

LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	./srcs/minishell.c	\
		./srcs/utils/str_dup.c \
		./srcs/utils/free_memory.c \
		./srcs/utils/readline.c \
		./srcs/utils/inits.c

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
