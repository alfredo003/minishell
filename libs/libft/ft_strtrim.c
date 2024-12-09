/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 08:50:27 by djoao             #+#    #+#             */
/*   Updated: 2024/05/20 08:50:39 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	char		*trimmed_str;
	size_t		len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = s1;
	while (*start && ft_strchr(set, *start))
		start++;
	end = s1 + ft_strlen(s1) - 1;
	while (end > start && ft_strchr(set, *end))
		end--;
	len = end - start + 1;
	trimmed_str = (char *)malloc(sizeof(char) * (len + 1));
	if (trimmed_str == NULL)
		return (NULL);
	ft_strlcpy(trimmed_str, start, len + 1);
	return (trimmed_str);
}
