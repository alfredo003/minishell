/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verifying_argument.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:13:48 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/05 17:13:51 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	verifying_next_type(t_mini *mini, int i)
{
	if (is_type(mini->tokens[i], 'R') || is_type(mini->tokens[i], 'T')
		|| is_type(mini->tokens[i], 'I'))
	{
		if (!mini->tokens[i + 1].str
			|| (is_type(mini->tokens[i + 1], 'R')
				|| is_type(mini->tokens[i + 1], 'T')
				|| is_type(mini->tokens[i + 1], 'I')
				|| is_type(mini->tokens[i + 1], 'P')))
		{
			ft_putstr_fd("minishell: "
				"syntax error near unexpected token1", 2);
			if (mini->tokens[i + 1].str)
				ft_putstr_fd(mini->tokens[i + 1].str, 2);
			else
				ft_putstr_fd("newline", 2);
			ft_putstr_fd("'\n", 2);
			mini->last_return = 258;
			return (0);
		}
	}
	return (1);
}

static int	verifying_previous_type(t_mini *mini, int i)
{
	if (is_type(mini->tokens[i], 'P'))
	{
		if (!mini->tokens[i + 1].str || !mini->tokens[i - 1].str
			|| is_type(mini->tokens[i - 1], 'R')
			|| is_type(mini->tokens[i - 1], 'T')
			|| is_type(mini->tokens[i - 1], 'I')
			|| is_type(mini->tokens[i - 1], 'P'))
		{
			ft_putstr_fd("minishell: "
				"syntax error near unexpected token ", 2);
			ft_putstr_fd(mini->tokens[i].str, 2);
			ft_putstr_fd("'\n", 2);
			mini->last_return = 258;
			return (0);
		}
	}
	return (1);
}

int	verifying_argument(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->tokens[i].str)
	{
		if (!verifying_next_type(mini, i)
			|| !verifying_previous_type(mini, i))
			return (0);
		i++;
	}
	return (1);
}
