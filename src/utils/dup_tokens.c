/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:27:25 by djoao             #+#    #+#             */
/*   Updated: 2025/01/20 13:27:29 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_heredoc_tokens(t_shell *shell, char *str_heredoc, int *i)
{
	shell->tokens[*i].str = ft_strdup("/bin/echo");
	shell->tokens[(*i)++].type = 'A';
	shell->tokens[*i].str = ft_strdup("-e");
	shell->tokens[(*i)++].type = 'A';
	shell->tokens[*i].str = str_heredoc;
	shell->tokens[(*i)++].type = 'A';
}

static void	copy_remaining_tokens(t_shell *shell, t_token *tokens, int *i)
{
	int	j;

	j = 0;
	if (tokens[0].str)
	{
		shell->tokens[*i].str = ft_strdup("|");
		shell->tokens[(*i)++].type = 'P';
	}
	while (tokens[j].str)
	{
		shell->tokens[*i + j].str = ft_strdup(tokens[j].str);
		shell->tokens[*i + j].type = tokens[j].type;
		j++;
	}
	shell->tokens[*i + j].str = NULL;
}

void	dup_tokens(t_shell *shell, t_token *tokens, char *str_heredoc)
{
	int	i;

	i = 0;

	int te =0;
	while(tokens[te].str)
	{
		te++;
	}
	shell->tokens = (t_token *)malloc(sizeof(t_token) * te +1);
	if (!shell->tokens)
		return ;
	if (str_heredoc && str_heredoc[0])
	{
		add_heredoc_tokens(shell, str_heredoc, &i);
		copy_remaining_tokens(shell, tokens, &i);
	}
	else
	{
		while (tokens[i].str)
		{
			shell->tokens[i].str = ft_strdup(tokens[i].str);
			shell->tokens[i].type = tokens[i].type;
			i++;
		}
		  
		shell->tokens[i].str = NULL;
	}
}
