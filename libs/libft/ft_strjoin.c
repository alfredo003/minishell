/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 08:45:45 by djoao             #+#    #+#             */
/*   Updated: 2024/05/20 08:45:50 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	joined_str = (char *)malloc(sizeof(char) * (ft_strlen(s1)
				+ ft_strlen(s2) + 1));
	if (joined_str == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		joined_str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		joined_str[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	joined_str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (joined_str);
}
