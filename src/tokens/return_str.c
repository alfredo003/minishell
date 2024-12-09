/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <mcaquart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 02:27:38 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/25 16:23:01 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../header/minishell.h"

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

	str = (char *)malloc(sizeof(char) * 100000);
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
			&& (is_separator(ptr[*i]) || ptr[*i] == ' '))
			break ;
		str[n++] = ptr[(*i)++];
	}
	str[n] = '\0';
	return (str);
}
