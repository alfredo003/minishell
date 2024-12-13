#include "minishell.h"

t_token	*organize_tokens(t_token *tokens)
{
	int		i;
	t_token	tmp[3];

	i = -1;
	while (tokens[++i].str)
	{
		if (is_type(tokens[i], 'R') || is_type(tokens[i], 'T')
			|| is_type(tokens[i], 'H') || is_type(tokens[i], 'I'))
		{
			if (tokens[i + 2].str && is_type(tokens[i + 2], 'A'))
			{
				tmp[0] = tokens[i];
				tmp[1] = tokens[i + 1];
				tmp[2] = tokens[i + 2];
				tokens[i] = tmp[2];
				tokens[i + 1] = tmp[0];
				tokens[i + 2] = tmp[1];
				i = 0;
			}
		}
	}
	return (tokens);
}

t_token	*initialize_tokens(void)
{
	t_token	*tokens;

	tokens = (t_token *)malloc(sizeof(t_token) * 10000);
	if (!tokens)
		return (NULL);
	ft_memset(tokens, 0, sizeof(t_token) * 10000);
	return (tokens);
}

t_token	*process_str(t_shell *shell, char *line)
{
	t_token	*tokens;

	tokens = initialize_tokens();
	if (!tokens)
		return (NULL);
	process_tokens(shell, line, tokens);
	return (tokens);
}


t_token	*gettokens(t_shell *shell, char *line)
{
	t_token	*tokens;

	tokens = process_str(shell, line);
	tokens = organize_tokens(tokens);
	return (tokens);
}
