/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:08:08 by achivela          #+#    #+#             */
/*   Updated: 2025/01/20 17:08:11 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFFER_SIZE 1000000000

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
# include <sys/wait.h>
# include "../libs/libft/libft.h"

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

typedef struct s_state
{
	char	in_single_quotes;
	char	in_double_quotes;
	size_t	delimiter_len;
	size_t	i;
	size_t	start;
	size_t	len;
}	t_state;

t_token	*gettokens(t_shell *shell, char *line);
t_token	*process_str(t_shell *shell, char *line);
t_env	*add_envirenoment(char *env_name, char *env_value, int equal);
t_env	*sort_env_list(t_env *head);

void	init_struct(t_shell *shell, char **env);
void	init_shell(t_shell *shell);
void	sigint_handler(int sig);
void	redir_and_exec(t_shell *shell, int pos_token, int pipe);
void	redir(t_shell *shell, char *file, char *type);
void	input(t_shell *shell, char *file);
void	handle_export(char **tmp, t_env **env, t_shell *mini);
void	dup_env(char **env, t_shell *shell, int equal);
void	ft_close(int fd);
void	ft_free_matrix(char **matrix);
void	ft_env(t_env *env, int type);
void	ft_export(char *args, t_env **env, int equal, int new_env);
void	ft_echo(char **args, t_shell *shell);
void	ft_cd(t_shell *shell, char **argument);
void	ft_exit(char **matrix, t_shell *shell);
void	execute_cmd(t_shell *shell, char **cmd);
void	increment_shell_level(t_shell *shell);
void	reset_std(t_shell *shell);
void	close_fds(t_shell *shell);
void	reset_fds(t_shell *shell);
void	handle_signals(void);
void	ft_unset_expanded(char *args, t_env **env);
void	ft_unset_non_expanded(char *args, t_env **env);
void	ft_free_all(t_shell *shell);
void	ft_free(void *ptr, int free_ptr);
void	free_tokens(t_token *head);

void	free_env(t_env *head);
void	toggle_quotes(char c, t_state *state);
void	sigquit(int sig);
void	ft_free_tokens(t_token *tokens);
void	dup_tokens(t_shell *shell, t_token *tokens, char *str_heredoc);
void	process_tokens(t_shell *shell, char *line, t_token *tokens);
void	free_str_and_set_null(char **str);

char	*ft_pwd(t_shell *shell);
char	*expand_variables(t_shell *mini, char *input, int in_heredoc);
char	*ft_getenv(t_env *env, char *var);
char	*get_separator(char *line, int *i);
char	*return_str(char *ptr, int *i, int *in_quotes);
char	**env_to_matrix(t_env *env, int i, int type);
char	**ft_split_advanced(const char *s, const char *delimiter);
char	*my_strndup(const char *s, size_t n);
char	**cmd_tab(t_token *tokens, int *pos_token);
char	*get_env_value(t_shell *shell, char *input, int *n);
char	**allocate_result(size_t count);
char	*heredoc(t_shell *shell, char *delimiter);
char	*strjoin_free(char *s1, char *s2, int free_s1, int free_s2);
char	type_str(char *str, int in_quotes);

size_t	count_loop(const char *s, const char *delimiter,
			t_state *state, size_t delimiter_len);
size_t	count_substrings(const char *s, const char *delimiter);

int		ft_readline(t_shell *shell, char **line);
int		handle_unset(char **tmp, t_env **env);
int		minipipe(t_shell *shell);
int		ignore_sep(char *line, int i);
int		ft_strisnum(const char *str);
int		exec_builtin(char **args, t_shell *shell);
int		nb_args(char **args);
int		whereis(const char *str, const char *needle);
int		numb_split(char **matrix);
int		verifying_argument(t_shell *shell);
int		check_delimiter(const char *s, const char *delimiter,
			t_state *state, size_t delimiter_len);
int		get_variable_length(t_shell *shell, char *input, int *n);
int		handle_return_value(t_shell *shell, int *n, int *len_aloc);
int		ft_can_be_add(char *str, int i, t_shell *shell);
int		ft_is_closed(char *str, int i, char quote);
int		ft_is_unclosed_quote(char *str, int i, char quote, t_shell *shell);
int		is_type(t_token token, char type);
int		verifying_heredoc(t_shell *shell, t_token *tokens, char **str_heredoc);
void	pip_process(char *line);

#endif
