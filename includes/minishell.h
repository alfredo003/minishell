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




void	process_quotes(char c, t_split_state *state);
void	handle_variable_expansion(char *input, t_split_state *state, int last_exit_code);
char	**finalize_token(t_split_state *state);
char	**ft_split_with_quotes_and_vars(char *input, int last_exit_code);
size_t	get_variable_length(char *input, size_t start);
int	expand_variable(char *input, t_split_state *state);
void	expand_all_args(t_split_state *state);
void	expand_last_exit_code(t_split_state *state, int last_exit_code);




int	process_quote(char **str);
int	size_token(char *str);
char *ft_strcpy(char *dest, const char *src);
char	*ft_strndup(const char *s, size_t n);
t_split_state	initialize_split_state(char *input);

#endif
