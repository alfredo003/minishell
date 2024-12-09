/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_str_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:39:56 by mcaquart          #+#    #+#             */
/*   Updated: 2024/11/01 22:39:58 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	skip_whitespace(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

static void	process_separator(char *line, int *i, t_token *matrix, int *j)
{
	char	*str;

	if (is_separator(line[*i]))
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

t_token	*initialize_tokens(void)
{
	t_token	*tokens;

	tokens = (t_token *)malloc(sizeof(t_token) * 10000);
	if (!tokens)
		return (NULL);
	ft_memset(tokens, 0, sizeof(t_token) * 10000);
	return (tokens);
}

void	free_str_and_set_null(char **str)
{
	ft_free(*str, 1);
	*str = NULL;
}

void	process_tokens(t_mini *mini, char *line, t_token *tokens)
{
	int		i;
	int		j;
	int		in_quotes;
	char	*str;

	i = 0;
	j = 0;
	while (line[i])
	{
		skip_whitespace(line, &i);
		str = return_str(line, &i, &in_quotes);
		str = expand_variables(mini, str, 0);
		if (str && str[0])
		{
			tokens[j].str = ft_strdup(str);
			tokens[j].type = type_str(str, in_quotes);
			j++;
		}
		skip_whitespace(line, &i);
		process_separator(line, &i, tokens, &j);
		free_str_and_set_null(&str);
	}
	tokens[j].str = NULL;
}
