#include "minishell.h"

static t_token	*organize_tokens(t_token *tokens)
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

void	process_tokens(t_shell *shell, char *line, t_token *tokens)
{
	int		i;
	int		j;
	int		verify;
	char	*str;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
            i++;
		str = get_substr(line, &i, &verify);
		str = expand_variables(shell, str, 0);
		if (str && str[0])
		{
			tokens[j].str = ft_strdup(str);
			tokens[j].type = type_str(str, verify);
			j++;
		}
		while (line[i] == ' ' || line[i] == '\t')
            i++;
		process_separator(line, &i, tokens, &j);
		ft_free(str, 1);
		str = NULL;
	}
	tokens[j].str = NULL;
}

static t_token *split_tokens(t_shell *shell, char *line)
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
	tokens = organize_tokens(tokens);
    return (tokens);
}