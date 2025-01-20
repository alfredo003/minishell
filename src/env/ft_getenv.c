/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achivela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:41:28 by achivela          #+#    #+#             */
/*   Updated: 2025/01/20 11:41:31 by achivela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_getenv(t_env *env, char *var)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (ft_strcmp(env_tmp->key, var) == 0)
		{
			if (env_tmp->equal == 1 && env_tmp->value)
				return (ft_strdup(env_tmp->value));
			else
				return (NULL);
		}
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

int	handle_return_value(t_shell *shell, int *n, int *len_aloc)
{
	shell->values.str1 = ft_itoa(shell->last_return);
	*len_aloc += ft_strlen(shell->values.str1);
	ft_free(shell->values.str1, 1);
	(*n)++;
	return (*len_aloc);
}

int	get_variable_length(t_shell *shell, char *input, int *n)
{
	char	*env_name;
	int		i;
	int		len_aloc;
	char	*env_value;

	i = 0;
	len_aloc = 0;
	(*n)++;
	if (input[*n] == '?')
		return (handle_return_value(shell, n, &len_aloc));
	env_name = malloc(ft_strlen(input) + 1);
	if (!env_name)
		return (0);
	while (input[*n] && (ft_isalnum(input[*n]) || input[*n] == '_'))
		env_name[i++] = input[(*n)++];
	env_name[i] = '\0';
	env_value = ft_getenv(shell->env, env_name);
	if (env_value)
		len_aloc += ft_strlen(env_value);
	ft_free(env_name, 1);
	ft_free(env_value, 1);
	return (len_aloc);
}
