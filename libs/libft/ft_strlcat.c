/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:00:00 by djoao             #+#    #+#             */
/*   Updated: 2024/05/17 18:00:03 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;
	size_t	total_len;
	size_t	i;

	d_len = 0;
	s_len = 0;
	total_len = 0;
	i = 0;
	while (dest[d_len] != '\0' && d_len < size)
		d_len++;
	while (src[s_len] != '\0')
		s_len++;
	total_len = d_len + s_len;
	if (d_len >= size)
		return (total_len);
	while (src[i] != '\0' && d_len + 1 < size)
	{
		dest[d_len] = src[i];
		i++;
		d_len++;
	}
	dest[d_len] = '\0';
	return (total_len);
}
