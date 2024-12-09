/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcaquart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:03:31 by mcaquart          #+#    #+#             */
/*   Updated: 2024/10/07 14:03:33 by mcaquart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_is_unclosed_quote(char *str, int i, char quote, t_mini *mini)
{
	if (mini->values.val1 == quote)
		return (0);
	else if (!mini->values.val1)
	{
		while (str[++i])
		{
			if (str[i] == quote)
				return (0);
		}
	}
	return (1);
}

int	ft_is_closed(char *str, int i, char quote)
{
	while (str[++i])
	{
		if (str[i] == quote)
			return (1);
	}
	return (0);
}

int	ft_can_be_add(char *str, int i, t_mini *mini)
{
	if ((str[i] == 34 || str[i] == 39))
	{
		if (str[i] == 34 && ft_is_unclosed_quote(str, i, str[i], mini))
			return (1);
		if (str[i] == 39 && ft_is_unclosed_quote(str, i, str[i], mini))
			return (1);
		if (!mini->values.val1)
			return (0);
		if ((str[i] == 34 && mini->values.val1 == 34))
			return (0);
		if ((str[i] == 39 && mini->values.val1 == 39))
			return (0);
	}
	return (1);
}

int	handle_return_value(t_mini *mini, int *n, int *len_aloc)
{
	mini->values.str1 = ft_itoa(mini->last_return);
	*len_aloc += ft_strlen(mini->values.str1);
	ft_free(mini->values.str1, 1);
	(*n)++;
	return (*len_aloc);
}

int	get_variable_length(t_mini *mini, char *input, int *n)
{
	char	*env_name;
	int		i;
	int		len_aloc;

	i = 0;
	len_aloc = 0;
	(*n)++;
	if (input[*n] == '?')
		return (handle_return_value(mini, n, &len_aloc));
	env_name = malloc(1000);
	if (!env_name)
		return (0);
	while (input[*n] && (ft_isalnum(input[*n]) || input[*n] == '_'))
		env_name[i++] = input[(*n)++];
	env_name[i] = '\0';
	mini->values.str1 = ft_getenv(mini->env, env_name);
	len_aloc += ft_strlen(mini->values.str1);
	ft_free(env_name, 1);
	ft_free(mini->values.str1, 1);
	return (len_aloc);
}
