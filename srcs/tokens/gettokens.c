#include "minishell.h"

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
		free_str_and_set_null(&str);
	}
	tokens[j].str = NULL;
}

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