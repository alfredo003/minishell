#include "minishell.h"

int	size_token(char *str)
{
	int	size;
	char	quote;

	size = 0;
	while (*str)
	{
		while (*str == ' ')
			str++;
		if (*str == '"' || *str == '\'')
		{
			quote = *str++;
			size++;
			while (*str && *str != quote)
				str++;
			if (!*str)
			{
				printf("Error: Unterminated quote\n");
				return (-1);
			}
				str++;
		}
		else if (*str && *str != ' ')
		{
			size++;
			while (*str && *str != ' ')
				str++;
		}
	}
	return (size);
}

char *ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = 0;
	i = 0;
	while (s[len] && len < n)
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return NULL;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	**initialize_tokens(char *input)
{
	char	**tokens;

	tokens = malloc((size_token(input) + 1) * sizeof(char *));
	if (!tokens)
	{
	printf("Allocation Error\n");
	exit(EXIT_FAILURE);
	}
	return (tokens);
}

char	*initialize_token(char *input)
{
	char	*token;

	token = malloc(ft_strlen(input) + 1);
	if (!token)
	{
		printf("Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	return (token);
}

void	process_quotes(char c, int *in_single_quotes, int *in_double_quotes)
{
	if (c == '\'' && !(*in_double_quotes))
		*in_single_quotes = !(*in_single_quotes);
	else if (c == '"' && !(*in_single_quotes))
		*in_double_quotes = !(*in_double_quotes);
}

void	handle_variable_expansion(char *input, size_t *i, char *token, size_t *token_pos)
{
	size_t	start;
	size_t	var_len;
	char	*var_name;
	char	*value;

	start = *i + 1;
	var_len = 0;
	while (ft_isalnum(input[start]) || input[start] == '_')
	{
		start++;
		var_len++;
	}
	if (var_len > 0)
	{
		var_name = ft_strndup(&input[*i + 1], var_len);
		value = getenv(var_name);
		free(var_name);

		if (value)
		{
			ft_strcpy(&token[*token_pos], value);
			*token_pos += ft_strlen(value);
		}
		*i = start;
	}
	else
	{
		printf("%zu Fui chamado\n", *token_pos);
		token[*token_pos] = input[*i];
		(*token_pos)++;
	}
}

int	is_delimiter(char c, int in_single_quotes, int in_double_quotes)
{
	return (c == ' ' && !in_single_quotes && !in_double_quotes);
}

void	handle_token_addition(char *token, size_t *token_pos, char **tokens, size_t *token_count)
{
	if (*token_pos > 0)
	{
		token[*token_pos] = '\0';
		tokens[*token_count] = ft_strdup(token);
		(*token_count)++;
		*token_pos = 0;
	}
}

char	**finalize_token(char *token, size_t *token_pos, char **tokens, size_t *token_count)
{
	if (*token_pos > 0)
	{
		token[*token_pos] = '\0';
		tokens[(*token_count)++] = ft_strdup(token);
	}
	tokens[*token_count] = NULL;
	free(token);
	return (tokens);
}

char	**ft_split_with_quotes_and_vars(char *input)
{
	size_t	i;
	size_t	token_pos;
	size_t	token_count;
	int		in_single_quotes;
	int		in_double_quotes;
	char	**tokens;
	char	*token;

	i = 0;
	token_pos = 0;
	token_count = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	tokens = initialize_tokens(input);
	token = initialize_token(input);
	while (input[i])
	{
		process_quotes(input[i], &in_single_quotes, &in_double_quotes);
	if (input[i] == '$' && in_single_quotes == 0)
	{
		handle_variable_expansion(input, &i, token, &token_pos);
		continue ;
	}
	if (is_delimiter(input[i], in_single_quotes, in_double_quotes))
		handle_token_addition(token, &token_pos, tokens, &token_count);
	else if (input[i] != '\'' && input[i] != '"')
	{
		printf("\nProcessando caractere: %c\n", input[i]);
		token[token_pos++] = input[i];
	}
	i++;
	}
	return (finalize_token(token, &token_pos, tokens, &token_count));
}
