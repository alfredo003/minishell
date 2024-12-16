#include "minishell.h"

void skip_whitespace(char **input)
{
	while (ft_isspace(**input))
		(*input)++;
}

char	*extract_quoted_token(char **input, char quote)
{
	char	*start;

	start = ++(*input);
	while (**input && **input != quote)
		(*input)++;
	if (**input == quote)
	{
		**input = '\0';
		(*input)++;
	}
	return (start);
}

char	*extract_regular_token(char **input)
{
	char	*start;

	start = *input;
	while (**input && !ft_isspace(**input) && **input != '|' && **input != '<' && **input != '>')
		(*input)++;
	if (**input)
	{
		**input = '\0';
		(*input)++;
	}
	return (start);
}

char	**allocate_tokens(size_t size)
{
	char	**tokens;

	tokens = malloc(sizeof(char *) * size);
	if (!tokens)
	{
		perror("malloc failed");
		return (NULL);
	}
	return (tokens);
}

char **tokenize_input(char *input)
{
	char	**tokens;
	char	*token;
	int	count;

	count = 0;
	tokens = NULL;
	tokens = allocate_tokens(1024);
	while (*input)
	{
		skip_whitespace(&input);
		if (*input == '\0')
			break ;
		if (*input == '"' || *input == '\'')
			token = extract_quoted_token(&input, *input);
		else
			token = extract_regular_token(&input);
		if (token)
			tokens[count++] = strdup(token);
	}
	tokens[count] = NULL;
	return (tokens);
}
