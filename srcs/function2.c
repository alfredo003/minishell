#include "minishell.h"

size_t	get_variable_length(char *input, size_t start)
{
	size_t	var_len;

	var_len = 0;
	while (ft_isalnum(input[start]) || input[start] == '_')
	{
		start++;
		var_len++;
	}
	return (var_len);
}

int	expand_variable(char *input, t_split_state *state)
{
	size_t	var_len;
	char	*var_name;
	char	*value;

	state->i++;
	var_len = get_variable_length(input, state->i);
	if (var_len > 0)
	{
		var_name = ft_strndup(&input[state->i], var_len);
		value = getenv(var_name);
		free(var_name);
		if (value)
		{
			ft_strcpy(&state->token[state->token_pos], value);
			state->token_pos += ft_strlen(value);
		}
		state->i += var_len;
		return (1);
	}
	state->i--;
	return (0);
}

void	expand_all_args(t_split_state *state)
{
	size_t	start;
	char	*value;

	start = state->i + 1;
	value = getenv("ALL_ARGUMENTS");
	if (value)
	{
		ft_strcpy(&state->token[state->token_pos], value);
		state->token_pos += ft_strlen(value);
	}
	state->i = start;
}

void	expand_last_exit_code(t_split_state *state, int last_exit_code)
{
	char	*exit_code_str;
	size_t	len;

	exit_code_str = ft_itoa(last_exit_code);
	len = ft_strlen(exit_code_str);
	ft_strcpy(&state->token[state->token_pos], exit_code_str);
	state->token_pos += len;
	free(exit_code_str);
	state->i += 2;
}
