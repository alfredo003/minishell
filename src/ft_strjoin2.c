/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aluzingu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:40:49 by aluzingu          #+#    #+#             */
/*   Updated: 2024/10/10 22:40:52 by aluzingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

#include <stdlib.h>

#include <stdlib.h>

static void	free_if_needed(char **ptr, int free_flag)
{
	if (free_flag)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*allocate_result2(char *s1, char *s2)
{
	size_t	total_len;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	return ((char *)malloc((total_len + 1) * sizeof(char)));
}

static void	copy_strings(char *result, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[i++] = s2[j++];
	}
	result[i] = '\0';
}

char	*ft_strjoin2(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*result;

	if (!s1 || !s2)
	{
		free_if_needed(&s1, free_s1);
		free_if_needed(&s2, free_s2);
		return (NULL);
	}
	result = allocate_result2(s1, s2);
	if (result == NULL)
		return (NULL);
	copy_strings(result, s1, s2);
	free_if_needed(&s1, free_s1);
	free_if_needed(&s2, free_s2);
	return (result);
}
