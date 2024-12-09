/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 22:40:04 by mcaquart          #+#    #+#             */
/*   Updated: 2024/11/01 22:40:06 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_token	*process_str(t_mini *mini, char *line)
{
	t_token	*tokens;

	tokens = initialize_tokens();
	if (!tokens)
		return (NULL);
	process_tokens(mini, line, tokens);
	return (tokens);
}
