/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:24:41 by djoao             #+#    #+#             */
/*   Updated: 2024/05/16 16:24:46 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	val;
	size_t			i;

	p = (unsigned char *)s;
	val = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		p[i] = val;
		i++;
	}
	return (s);
}
