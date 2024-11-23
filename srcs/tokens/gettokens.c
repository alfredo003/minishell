#include "minishell.h"

static t_token *split_token(t_shell *shell, char *line)
{
    t_token *tokens;

    tokens = (t_token *)malloc(sizeof(t_token) * 10000);
	if (!tokens)
		return (NULL);
	ft_memset(tokens, 0, sizeof(t_token) * 10000);
    process_tokens(shell, line, tokens);
    return (tokens);
}

t_token *gettokens(t_shell *shell, char *line)
{
    t_token *tokens;

    tokens = split_tokens(shell, line);
    return (tokens);
}