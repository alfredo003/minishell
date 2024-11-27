# ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

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
	int			in;
	int			out;
	int			fdin;
	int			fdout;
	int			pipin;
	int			pipout;
	int			pid;
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
t_token *gettokens(t_shell *shell, char *line);
void verify_line(t_shell *shell, char *line);
char	*get_substr(char *ptr, int *i, int *in_quotes);
int	is_type(t_token token, char type);
char	type_str(char *str, int in_quotes);
int	is_separator(char c);
#endif 
