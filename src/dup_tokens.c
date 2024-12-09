/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:54:33 by mcaquart          #+#    #+#             */
/*   Updated: 2024/11/01 22:54:34 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	add_heredoc_tokens(t_mini *mini, char *str_heredoc, int *i)
{
	mini->tokens[*i].str = ft_strdup("/bin/echo");
	mini->tokens[(*i)++].type = 'A';
	mini->tokens[*i].str = ft_strdup("-e");
	mini->tokens[(*i)++].type = 'A';
	mini->tokens[*i].str = str_heredoc;
	mini->tokens[(*i)++].type = 'A';
}

static void	copy_remaining_tokens(t_mini *mini, t_token *tokens, int *i)
{
	int	j;

	j = 0;
	if (tokens[0].str)
	{
		mini->tokens[*i].str = ft_strdup("|");
		mini->tokens[(*i)++].type = 'P';
	}
	while (tokens[j].str)
	{
		mini->tokens[*i + j].str = ft_strdup(tokens[j].str);
		mini->tokens[*i + j].type = tokens[j].type;
		j++;
	}
	mini->tokens[*i + j].str = NULL;
}

void	dup_tokens(t_mini *mini, t_token *tokens, char *str_heredoc)
{
	int	i;

	i = 0;
	mini->tokens = (t_token *)malloc(sizeof(t_token) * 10000);
	if (!mini->tokens)
		return ;
	if (str_heredoc && str_heredoc[0])
	{
		add_heredoc_tokens(mini, str_heredoc, &i);
		copy_remaining_tokens(mini, tokens, &i);
	}
	else
	{
		while (tokens[i].str)
		{
			mini->tokens[i].str = ft_strdup(tokens[i].str);
			mini->tokens[i].type = tokens[i].type;
			i++;
		}
		mini->tokens[i].str = NULL;
	}
}
