/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_advenced.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:21:12 by djoao             #+#    #+#             */
/*   Updated: 2025/01/20 13:21:16 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_substring(char **result, size_t index
		, const char *start, size_t length)
{
	result[index] = my_strndup(start, length);
	return (result[index] != NULL);
}

static int	process_loop(char **result, const char *s
	, const char *delimiter, t_state *state)
{
	size_t	current;

	current = 0;
	while (state->i < state->len)
	{
		toggle_quotes(s[state->i], state);
		if (!state->in_single_quotes && !state->in_double_quotes)
		{
			if (check_delimiter(s, delimiter, state, state->delimiter_len))
			{
				if (!add_substring(result, current++, s
						+ state->start, state->i - state->start))
					return (0);
				state->start = state->i + state->delimiter_len;
			}
		}
		state->i++;
	}
	return (add_substring(result, current, s
			+ state->start, state->i - state->start));
}

static int	process_substrings(char **result, const char *s,
		const char *delimiter)
{
	t_state	state;

	state.i = 0;
	state.start = 0;
	state.len = ft_strlen(s);
	state.in_single_quotes = 0;
	state.in_double_quotes = 0;
	state.delimiter_len = ft_strlen(delimiter);
	return (process_loop(result, s, delimiter, &state));
}

char	**ft_split_advanced(const char *s, const char *delimiter)
{
	size_t		count;
	char		**result;

	count = count_substrings(s, delimiter);
	result = allocate_result(count);
	if (!result)
		return (NULL);
	if (!process_substrings(result, s, delimiter))
	{
		ft_free(result, 1);
		return (NULL);
	}
	return (result);
}
