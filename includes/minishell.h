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

void	cd_command(char **args);
void	pwd_command(void);
void	export_command(char **args);
char	**ft_split_with_quotes_and_vars(char *input);
char	**finalize_token(char *token, size_t *token_pos, char **tokens, size_t *token_count);
void	handle_token_addition(char *token, size_t *token_pos, char **tokens, size_t *token_count);
int	is_delimiter(char c, int in_single_quotes, int in_double_quotes);
void	handle_variable_expansion(char *input, size_t *i, char *token, size_t *token_pos);
void	process_quotes(char c, int *in_single_quotes, int *in_double_quotes);
char	*initialize_token(char *input);
char	**initialize_tokens(char *input);
char	*ft_strndup(const char *s, size_t n);
char *ft_strcpy(char *dest, const char *src);
int	size_token(char *str);

#endif
