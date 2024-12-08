#include "minishell.h"

void	process_quotes(char c, t_split_state *state)
{
	if (c == '\'' && !(state->in_double_quotes))
		state->in_single_quotes = !(state->in_single_quotes);
	else if (c == '"' && !(state->in_single_quotes))
		state->in_double_quotes = !(state->in_double_quotes);
}

void	handle_variable_expansion(char *input, t_split_state *state, int last_exit_code)
{
	if (input[state->i + 1] == '@')
		expand_all_args(state);
	else if (input[state->i + 1] == '?')
		expand_last_exit_code(state, last_exit_code);
	else if (expand_variable(input, state) == 0)
	{
		state->token[state->token_pos] = input[state->i];
		state->token_pos++;
		state->i++;
	}
}

int	is_delimiter(char c, t_split_state *state)
{
	return (c == ' ' && !state->in_single_quotes && !state->in_double_quotes);
}

void	handle_token_addition(t_split_state *state)
{
	if (state->token_pos > 0)
	{
		state->token[state->token_pos] = '\0';
		state->tokens[state->token_count] = ft_strdup(state->token);
		state->token_count++;
		state->token_pos = 0;
	}
}

char	**finalize_token(t_split_state *state)
{
	if (state->token_pos > 0)
	{
		state->token[state->token_pos] = '\0';
		state->tokens[state->token_count++] = ft_strdup(state->token);
	}
	state->tokens[state->token_count] = NULL;
	free(state->token);
	state->token = NULL;
	return (state->tokens);
}

char	**ft_split_with_quotes_and_vars(char *input, int last_exit_code)
{
	t_split_state	state;

	state = initialize_split_state(input);
	while (input[state.i])
	{
		process_quotes(input[state.i], &state);
	if (input[state.i] == '$' && state.in_single_quotes == 0)
	{
		handle_variable_expansion(input, &state, last_exit_code);
		continue ;
	}
	if (is_delimiter(input[state.i], &state))
		handle_token_addition(&state);
	else if (input[state.i] != '\'' && input[state.i] != '"')
		state.token[state.token_pos++] = input[state.i];
	state.i++;
	}
	return (finalize_token(&state));
}
