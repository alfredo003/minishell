/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoao <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:20:15 by djoao             #+#    #+#             */
/*   Updated: 2025/01/20 13:20:18 by djoao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quote_is_closed(char *str, int i, int quote)
{
	while (str[++i])
	{
		if (str[i] == quote)
			return (1);
	}
	return (0);
}

static void	return_str_auxilary(int *single_quote, int *double_quote,
	char *ptr, int *i)
{
	if (ptr[*i] == 34)
	{
		if (*double_quote == 0)
		{
			if (ft_quote_is_closed(ptr, *i, 34))
				*double_quote ^= 1;
		}
		else
			*double_quote = 0;
	}
	else if (ptr[*i] == 39)
	{
		if (*single_quote == 0)
		{
			if (ft_quote_is_closed(ptr, *i, 39))
				*single_quote ^= 1;
		}
		else
			*single_quote = 0;
	}
}

char	*return_str(char *ptr, int *i, int *in_quotes)
{
	char	*str;
	int		n;
	int		single_quote;
	int		double_quote;

	int test = ft_strlen(ptr);
	str = (char *)malloc(sizeof(char) * test);
	if (!str)
		return (NULL);
	n = 0;
	single_quote = 0;
	double_quote = 0;
	*in_quotes = 0;
	while (ptr[*i])
	{
		return_str_auxilary(&single_quote, &double_quote, ptr, i);
		if (double_quote == 1 || single_quote == 1)
			*in_quotes = 1;
		if (double_quote == 0 && single_quote == 0
			&& ((ptr[*i] == '|' || ptr[*i] == '>'
					|| ptr[*i] == '<') || ptr[*i] == ' '))
			break ;
		str[n++] = ptr[(*i)++];
	}
	str[n] = '\0';
	return (str);
}
