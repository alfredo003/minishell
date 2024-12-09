/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifying_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:46:48 by mcaquart          #+#    #+#             */
/*   Updated: 2024/11/01 22:46:50 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	handle_syntax_error(void)
{
	ft_putendl_fd("minishell: syntax error near unexpected token", 2);
	return (258);
}

static int	process_delimiter(t_mini *mini, t_token *tokens, int i,
	char **str_heredoc)
{
	t_token	delimiter;

	if (tokens[i + 1].str)
	{
		delimiter = tokens[i + 1];
		if (is_type(delimiter, 'I') || is_type(delimiter, 'R')
			|| is_type(delimiter, 'T') || is_type(delimiter, 'H')
			|| is_type(delimiter, 'P'))
			return (handle_syntax_error());
		*str_heredoc = heredoc(mini, delimiter.str);
		ft_free(tokens[i + 1].str, 1);
		tokens[i + 1].str = NULL;
	}
	else
		return (handle_syntax_error());
	ft_free(tokens[i].str, 1);
	tokens[i].str = NULL;
	return (1);
}

int	verifying_heredoc(t_mini *mini, t_token *tokens, char **str_heredoc)
{
	int	i;

	i = -1;
	*str_heredoc = NULL;
	while (tokens[++i].str)
		if (is_type(tokens[i], 'H'))
			return (process_delimiter(mini, tokens, i, str_heredoc));
	return (0);
}
