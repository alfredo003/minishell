#include "minishell.h"

static int	handle_syntax_error(void)
{
	ft_putendl_fd("minishell: syntax error near unexpected token", 2);
	return (258);
}

static int	process_delimiter(t_shell *shell, t_token *tokens, int i,
	char **str_heredoc)
{
	t_token	delimiter;

	if (tokens[i + 1].str)
	{
		delimiter = tokens[i + 1];
		if (is_type(delimiter, 'I') || is_type(delimiter, 'R')
			|| is_type(delimiter, 'T') || is_type(delimiter, 'H')
			|| is_type(delimiter, 'P'))
			return (handle_syntax_error());
		*str_heredoc = heredoc(shell, delimiter.str);
		ft_free(tokens[i + 1].str, 1);
		tokens[i + 1].str = NULL;
	}
	else
		return (handle_syntax_error());
	ft_free(tokens[i].str, 1);
	tokens[i].str = NULL;
	return (1);
}

int	verifying_heredoc(t_shell *shell, t_token *tokens, char **str_heredoc)
{
	int	i;

	i = -1;
	*str_heredoc = NULL;
	while (tokens[++i].str)
		if (is_type(tokens[i], 'H'))
			return (process_delimiter(shell, tokens, i, str_heredoc));
	return (0);
}
