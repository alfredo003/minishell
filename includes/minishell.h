# ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redirection
{
	char	*file;
	int	type;
	struct s_redirection	*next;
}	t_redirection;

typedef struct	s_command
{
	char	**args;
	t_redirection	*redirections;
	struct s_command	*next;
}	t_command;

typedef struct	s_shell
{
	t_env	*env;
	t_command	*commands;
	int	exit_status;
}	t_shell;

//UTILS
int	ft_isspace(int c);
char *ft_strcpy(char *dest, const char *src);
char	*ft_strndup(const char *s, size_t n);

//ENVIRONMENT
t_env	*create_env_node(const char *env_var);
void	free_env_list(t_env *env);
t_env	*convert_to_env_list(char **envp);

//TOKENS
void skip_whitespace(char **input);
char	*extract_quoted_token(char **input, char quote);
char	*extract_regular_token(char **input);
char	**allocate_tokens(size_t size);
char **tokenize_input(char *input);

//parse_tokens
t_command	*create_new_command(void);
void	add_argument(t_command *command, const char *arg);
void	add_redirection(t_command *command, int type, const char *file);
t_command	*initialize_command(t_command **head, t_command *current);
t_command	*handle_pipe(t_command *current);
int	get_redirection_type(const char *token);
int	handle_redirection(t_command *current, char **tokens);
t_command	*check_command_allocation(t_command *current);
t_command	*parse_tokens(char **tokens);

#endif
