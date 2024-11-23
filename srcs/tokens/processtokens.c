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
		str = return_str(line, &i, &verify);
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