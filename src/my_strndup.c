/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:40:32 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 15:40:33 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*my_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < n && s[i] != '\0')
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}
