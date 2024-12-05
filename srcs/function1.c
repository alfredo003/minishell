#include "minishell.h"

int	process_quote(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str && **str != quote)
		(*str)++;
	if (!**str)
	{
		printf("Error: Unterminated quote\n");
		return (-1);
	}
	(*str)++;
	return (1);
}

int	size_token(char *str)
{
	int	size;

	size = 0;
	while (*str)
	{
		while (*str == ' ')
			str++;
		if (*str == '"' || *str == '\'')
		{
			if (process_quote(&str) == -1)
				return (-1);
			size++;
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

void	handle_variable_expansion(char *input, size_t *i, char *token, size_t *token_pos, int last_exit_code)
{
	if (input[*i + 1] == '@')
	{
		expand_all_args(i, token, token_pos);
		return ;
	}
	if (input[*i + 1] == '?')
	{
		expand_last_exit_code(i, token, token_pos, last_exit_code);
		return ;
	}
	if (expand_variable(input, i, token, token_pos) == 0)
	{
		token[*token_pos] = input[*i];
		(*token_pos)++;
		(*i)++;
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

t_split_state	initialize_split_state(char *input)
{
	t_split_state	state;

	state.i = 0;
	state.token_pos = 0;
	state.token_count = 0;
	state.in_single_quotes = 0;
	state.in_double_quotes = 0;
	state.tokens = initialize_tokens(input);
	state.token = initialize_token(input);
	return (state);
}

char	**ft_split_with_quotes_and_vars(char *input, int last_exit_code)
{
	t_split_state	state;

	state = initialize_split_state(input);
	while (input[state.i])
	{
		process_quotes(input[state.i], &state.in_single_quotes, &state.in_double_quotes);
	if (input[state.i] == '$' && state.in_single_quotes == 0)
	{
		handle_variable_expansion(input, &state.i, state.token, &state.token_pos, last_exit_code);
		continue ;
	}
	if (is_delimiter(input[state.i], state.in_single_quotes, state.in_double_quotes))
		handle_token_addition(state.token, &state.token_pos, state.tokens, &state.token_count);
	else if (input[state.i] != '\'' && input[state.i] != '"')
		state.token[state.token_pos++] = input[state.i];
	state.i++;
	}
	return (finalize_token(state.token, &state.token_pos, state.tokens, &state.token_count));
}
