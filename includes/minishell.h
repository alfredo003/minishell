# ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_split_state
{
	size_t	i;
	size_t	token_pos;
	size_t	token_count;
	int	in_single_quotes;
	int	in_double_quotes;
	char	**tokens;
	char	*token;
}	t_split_state;



void	cd_command(char **args);
void	pwd_command(void);
void	export_command(char **args);
int	process_quote(char **str);






int	size_token(char *str);
char	**initialize_tokens(char *input);
char	*initialize_token(char *input);
void	process_quotes(char c, int *in_single_quotes, int *in_double_quotes);
void	handle_variable_expansion(char *input, size_t *i, char *token, size_t *token_pos, int last_exit_code);
char	**finalize_token(char *token, size_t *token_pos, char **tokens, size_t *token_count);
char	**ft_split_with_quotes_and_vars(char *input, int last_exit_code);
int	expand_variable(char *input, size_t *i, char *token, size_t *token_pos);
void	expand_all_args(size_t *i, char *token, size_t *token_pos);
void	expand_last_exit_code(size_t *i, char *token, size_t *token_pos, int last_exit_code);




char *ft_strcpy(char *dest, const char *src);
char	*ft_strndup(const char *s, size_t n);

#endif
