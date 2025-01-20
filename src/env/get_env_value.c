/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:08:30 by achivela          #+#    #+#             */
/*   Updated: 2025/01/20 12:08:33 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*get_env_value(t_shell *shell, char *input, int *n)
{
	char	*env_name;
	char	*env_value;
	int		i;

	i = 0;
	if (input[*n] == '?')
	{
		env_value = ft_itoa(shell->last_return);
		(*n)++;
	}
	else
	{
		env_name = malloc(1000);
		if (!env_name)
			return (NULL);
		while (input[*n] && (ft_isalnum(input[*n]) || input[*n] == '_'))
			env_name[i++] = input[(*n)++];
		env_name[i] = '\0';
		env_value = ft_getenv(shell->env, env_name);
		ft_free(env_name, 1);
	}
	return (env_value);
}
