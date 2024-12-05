# ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdbool.h>

typedef struct s_token
{
	char	*str;
	char	type;
}	t_token;

typedef struct s_env
{
	char			*key;
	int				equal;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_values
{
	int		val1;
	int		val2;
	char	*str1;
	char	*str2;
}	t_values;

typedef struct s_shell
{
	t_token		*tokens;
	t_env		*env;
	t_env		*env_copy;
	int			charge;
	int			parent;
	int			last_return;
	int			no_exec;
	int			exit_status;
	t_values	values;
}	t_shell;

void	dup_env(char **env, t_shell *shell);
void	free_matrix(char **matrix); 
int	ft_readline(t_shell *shell, char **line);
void	init_params(char **env, t_shell shell);
void	init_shell(t_shell *shell);
void	ft_free(void *ptr, int free_ptr);
void	free_tokens(t_token *tokens);
t_token *gettokens(t_shell *shell, char *line);
void verify_line(t_shell *shell, char *line);
char	*get_substr(char *ptr, int *i, int *in_quotes);
void	tokens_dup(t_shell *shell, t_token *tokens, char *str_heredoc);
int	is_type(t_token token, char type);
char	type_str(char *str, int in_quotes);
int	is_separator(char c);
char	*expand_variables(t_shell *shell, char *input, int in_heredoc);
void	process_separator(char *line, int *i, t_token *matrix, int *j);
char	*get_separator(char *line, int *i);
int	verifying_heredoc(t_shell *shell, t_token *tokens, char **str_heredoc);
int	verifying_argument(t_shell *shell);
void	redirect_exec(t_shell *shell, int pos_token, int pipe);
int	ft_is_unclosed_quote(char *str, int i, char quote, t_shell *shell);
int	ft_is_closed(char *str, int i, char quote);
int	ft_can_be_add(char *str, int i, t_shell *shell);
int	handle_return_value(t_shell *shell, int *n, int *len_aloc);
int	get_variable_length(t_shell *shell, char *input, int *n);
char	*get_env_value(t_shell *shell, char *input, int *n);
char	*ft_getenv(t_env *env, char *var);
char	**cmd_tab(t_token *tokens, int *pos_token);
void	execute_cmd(t_shell *shell, char **cmd);
char	*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2);
char	*heredoc(t_shell *shell, char *delimiter);
#endif
