/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:05:20 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/09 05:26:24 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**cmd_tab(t_token *tokens, int *pos_token)
{
	char	**tab;
	int		i;
	int		j;

	if (!tokens)
		return (NULL);
	i = *pos_token;
	j = 0;
	while (tokens[i].str && is_type(tokens[i], 'A'))
	{
		i++;
		j++;
	}
	tab = malloc(sizeof(char *) * (j + 1));
	if (!tab)
		return (NULL);
	ft_memset(tab, 0, sizeof(char *) * (j + 1));
	i = 0;
	while (tokens[*pos_token].str && is_type(tokens[*pos_token], 'A'))
	{
		tab[i++] = ft_strdup(tokens[*pos_token].str);
		*pos_token += 1;
	}
	tab[i] = NULL;
	return (tab);
}
