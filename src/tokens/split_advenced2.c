#include "minishell.h"

void	toggle_quotes(char c, t_state *state)
{
	if (c == 39)
		state->in_single_quotes = !state->in_single_quotes;
	else if (c == 34)
		state->in_double_quotes = !state->in_double_quotes;
}

int	check_delimiter(const char *s, const char *delimiter
	, t_state *state, size_t delimiter_len)
{
	if (state->i + delimiter_len <= state->len
		&& ft_strncmp(s + state->i, delimiter, delimiter_len) == 0)
	{
		state->i += delimiter_len - 1;
		return (1);
	}
	return (0);
}

size_t	count_loop(const char *s, const char *delimiter
	, t_state *state, size_t delimiter_len)
{
	size_t	count;

	count = 0;
	while (state->i < state->len)
	{
		toggle_quotes(s[state->i], state);
		if (!state->in_single_quotes && !state->in_double_quotes)
		{
			if (check_delimiter(s, delimiter, state, delimiter_len))
				count++;
		}
		state->i++;
	}
	return (count);
}

size_t	count_substrings(const char *s, const char *delimiter)
{
	size_t	delimiter_len;
	size_t	count;
	t_state	state;

	state.i = 0;
	state.len = strlen(s);
	state.in_single_quotes = 0;
	state.in_double_quotes = 0;
	delimiter_len = strlen(delimiter);
	count = count_loop(s, delimiter, &state, delimiter_len);
	return (count + 1);
}

char	**allocate_result(size_t count)
{
	char	**result;

	result = (char **)malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[count] = NULL;
	return (result);
}