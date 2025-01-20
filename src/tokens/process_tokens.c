#include "minishell.h"

static void	process_separator(char *line, int *i, t_token *matrix, int *j)
{
	char	*str;

	if (line[*i] == '|' || line[*i] == '>' || line[*i] == '<')
	{
		str = get_separator(line, i);
		if (str && str[0])
		{
			if (*j > 0 && matrix[*j - 1].str && is_type(matrix[*j - 1], 'P'))
			{
				matrix[(*j)].str = ft_strdup("echo");
				matrix[(*j)].type = 'A';
				(*j)++;
			}
			matrix[(*j)].str = str;
			matrix[(*j)].type = type_str(str, 0);
			(*j)++;
		}
	}
}

void	process_tokens(t_shell *shell, char *line, t_token *tokens)
{
	int		i;
	int		j;
	int		in_quotes;
	char	*str;

	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		str = return_str(line, &i, &in_quotes);
		str = expand_variables(shell, str, 0);
		if (str && str[0])
		{
			tokens[j].str = ft_strdup(str);
			tokens[j].type = type_str(str, in_quotes);
			j++;
		}
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		process_separator(line, &i, tokens, &j);
		free_str_and_set_null(&str);
	}
	tokens[j].str = NULL;
}
