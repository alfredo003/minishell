/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:17:01 by djoao             #+#    #+#             */
/*   Updated: 2024/05/17 16:17:05 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	const char	*s;
	size_t		i;
	size_t		o;
	char		*d;

	s = src;
	d = dest;
	i = 0;
	o = 0;
	while (s[o] != '\0')
	{
		o++;
	}
	if (size == 0)
		return (o);
	while (s[i] != '\0' && i < (size - 1))
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (o);
}
